/****************************************************************************************/
/*  Render.cpp                                                                          */
/*                                                                                      */
/*  Author: John Pollard                                                                */
/*  Description: Code to render polys under D3D                                         */
/*                                                                                      */
/*  The contents of this file are subject to the Genesis3D Public License               */
/*  Version 1.01 (the "License"); you may not use this file except in                   */
/*  compliance with the License. You may obtain a copy of the License at                */
/*  http://www.genesis3d.com                                                            */
/*                                                                                      */
/*  Software distributed under the License is distributed on an "AS IS"                 */
/*  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See                */
/*  the License for the specific language governing rights and limitations              */
/*  under the License.                                                                  */
/*                                                                                      */
/*  The Original Code is Genesis3D, released March 25, 1999.                            */
/*  Genesis3D Version 1.1 released November 15, 1999                                    */
/*  Copyright (C) 1999 WildTangent, Inc. All Rights Reserved                            */
/*                                                                                      */
/****************************************************************************************/
#include <Windows.h>
#include <stdio.h>

#include "D3DDrv.h"
#include "DCommon.h"
#include "Render.h"
#include "Scene.h"
#include "GSpan.h"
#include "D3D_Fx.h"
#include "D3DCache.h"
#include "D3D_Err.h"
#include "THandle.h"

#include "PCache.h"










#define SNAP_VERT(v)  ( ( v )  = ( float )( ( long )( ( v ) * 16 ) ) / 16.0f )

geBoolean DRIVERCC RenderGouraudPoly(DRV_TLVertex *Pnts, int32 NumPoints, uint32 Flags)
{
	int32			i;
	DRV_TLVertex	*pPnts;
	D3DTLVERTEX		D3DPnts[30], *pD3DPnts;
	float			ZRecip;
	float			Alpha;

	if(!AppInfo.RenderingIsOK)
		return	TRUE;

	if (Flags & DRV_RENDER_FLUSH)
	{
		if (!PCache_FlushWorldPolys())
			return FALSE;
		if (!PCache_FlushMiscPolys())
			return FALSE;
	}

	Alpha = Pnts->a;
	
	D3DBlendFunc (D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA);

	D3DSetTexture(0, NULL);
	
	int32 SAlpha = (int32)Alpha<<24;
	pPnts = Pnts;
	pD3DPnts = D3DPnts;
	for (i=0; i< NumPoints; i++)
	{
		ZRecip = 1/pPnts->z;

		pD3DPnts->sx = pPnts->x;
		pD3DPnts->sy = pPnts->y;
		pD3DPnts->sz = (1.0f - ZRecip);		// ZBUFFER
		pD3DPnts->rhw = ZRecip;
		pD3DPnts->color = SAlpha | ((int32)pPnts->r<<16) | ((int32)pPnts->g<<8) | (int32)pPnts->b;

		if (AppInfo.FogEnable && !(Flags & DRV_RENDER_POLY_NO_FOG)) // poly fog
		{
			DWORD	FogVal;
			float	Val;

			Val = pPnts->z;

			if (Val > AppInfo.FogEnd)
				Val = AppInfo.FogEnd;

			FogVal = (DWORD)((AppInfo.FogEnd-Val)/(AppInfo.FogEnd-AppInfo.FogStart)*255.0f);
		
			if (FogVal < 0)
				FogVal = 0;
			else if (FogVal > 255)
				FogVal = 255;
		
			pD3DPnts->specular = (FogVal<<24);		// Alpha component in specular is the fog value (0...255)
		}
		else
			pD3DPnts->specular = 0;

		pPnts++;
		pD3DPnts++;
	}

	D3DTexturedPolyOld(D3DPnts, NumPoints);

	if (Flags & DRV_RENDER_FLUSH)
	{
		AppInfo.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FLUSHBATCH, 0);
		AppInfo.lpD3DDevice->EndScene();
		AppInfo.lpD3DDevice->BeginScene();
	}

	return TRUE;
}

geBoolean DRIVERCC RenderWorldPoly(DRV_TLVertex *Pnts, int32 NumPoints, geRDriver_THandle *THandle, DRV_TexInfo *TexInfo, DRV_LInfo *LInfo, uint32 Flags)
{
	if(!AppInfo.RenderingIsOK)
	{
		return	TRUE;
	}
	else if (Flags & DRV_RENDER_FLUSH)
	{
		if (!PCache_FlushWorldPolys())
			return FALSE;
	}

	
	D3DDRV.NumRenderedPolys++;
	
	// Insert the poly into the world cache, for later rendering
	PCache_InsertWorldPoly(Pnts, NumPoints, THandle, TexInfo, LInfo, Flags);

	if (Flags & DRV_RENDER_FLUSH)
	{
		if (!PCache_FlushWorldPolys())
			return FALSE;
	}

	return TRUE;
}

geBoolean DRIVERCC RenderMiscTexturePoly(DRV_TLVertex *Pnts, int32 NumPoints, geRDriver_THandle *THandle, uint32 Flags)
{
	if(!AppInfo.RenderingIsOK)
	{
		return	TRUE;
	}
	else if (Flags & DRV_RENDER_FLUSH)
	{
		PCache_FlushMiscPolys();
	}
				
	PCache_InsertMiscPoly(Pnts, NumPoints, THandle, Flags);

	if (Flags & DRV_RENDER_FLUSH)
	{
		PCache_FlushMiscPolys();
	}

	return TRUE;
}

geBoolean DRIVERCC DrawDecal(geRDriver_THandle *THandle, RECT *SRect, int32 x, int32 y)
{
	RECT	SRect2, *pSRect;
	int32	Width, Height;
	HRESULT	ddrval;

	if(!AppInfo.RenderingIsOK)
		return	TRUE;

	if (!SRect)
	{
		SRect2.left = 0;
		SRect2.right = THandle->Width;
		SRect2.top = 0;
		SRect2.bottom = THandle->Height;
		pSRect = &SRect2;
		Width = (THandle->Width);
		Height = (THandle->Height);
	}
	else
	{
		pSRect = SRect;
		Width = (pSRect->right - pSRect->left)+1;
		Height = (pSRect->bottom - pSRect->top)+1;
	}
	
	if (x + Width <= 0)
		return TRUE;
	if (y + Height <= 0)
		return TRUE;

	if (x >= ClientWindow.Width)
		return TRUE;
	
	if (y >= ClientWindow.Height)
		return TRUE;
	
	if (x + Width >= (ClientWindow.Width-1))
		pSRect->right -= ((x + Width) - (ClientWindow.Width-1));
	if (y + Height >= (ClientWindow.Height-1))
		pSRect->bottom -= ((y + Height) - (ClientWindow.Height-1));

	if (x < 0)
	{
		pSRect->left += -x;
		x=0;
	}
	if (y < 0)
	{
		pSRect->top += -y;
		y=0;
	}
	
	RECT	DRect;

	Width = (pSRect->right - pSRect->left);
	Height = (pSRect->bottom - pSRect->top);

	DRect.left = x;
	DRect.right = x+Width;
	DRect.top = y;
	DRect.bottom = y+Height;
	
	ddrval= AppInfo.lpBackBuffer->Blt(&DRect, THandle->MipData[0].Surface, pSRect, 
		             (DDBLT_KEYSRC | DDBLT_WAIT), NULL);

	if(ddrval==DDERR_SURFACELOST)
	{
		if (!D3DMain_RestoreAllSurfaces())
			return	GE_FALSE;
	}

	return GE_TRUE;
}

