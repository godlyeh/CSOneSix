/***
*
*	Copyright (c) 1999, 2000 Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#ifndef USERCMD_H
#define USERCMD_H
#ifdef _WIN32
#pragma once
#endif

typedef struct usercmd_s
{
	short	lerp_msec;//0x0      // Interpolation time on client
	byte	msec; //0x2           // Duration in ms of command
	vec3_t	viewangles; //0x3     // Command view angles.

// intended velocities
	float	forwardmove; //0xF    // Forward velocity.
	float	sidemove; //0x13      // Sideways velocity.
	float	upmove; //0x17        // Upward velocity.
	byte	lightlevel; //1B    // Light level at spot where we are standing.
	unsigned short  buttons; //1C //  // Attack buttons
	byte    impulse; //1D         // Impulse command issued.
	byte	weaponselect; //1E	// Current weapon id

// Experimental player impact stuff.
	int		impact_index; //1F
	vec3_t	impact_position; //23
} usercmd_t;

#endif // USERCMD_H