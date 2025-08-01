/* See LICENSE file for copyright and license details. */
#define TERMINAL "alacritty"
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:size=13" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#00a0b4"; //"#005577";
static const char col_orange[]      = "#ffbb00";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2,  col_orange  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance	title           tags 	mask	isfloating	 isterminal	noswallow	monitor */
	{ "Gimp",	NULL,		NULL,		0,	1,	0,		 0,		-1 },
	{ "wine",	NULL,		NULL,		0,	1,	0,		 0,		-1 },
	{ "steam",	NULL,		NULL,		0,	1,	0,		 0,		-1 },
	{ "firefox", 	NULL,		NULL,		2,	0,	1,		-1,		-1 },
	{ "zoom", 	NULL,		NULL,		4,	4,	1,		-1,		-1 },
	{ "alacritty", 	NULL,		NULL,		0,	0,	1,		 0,		-1 },
	{ NULL,	  	NULL,		"Event Tester",	0,	0,	0,		 1,		-1 } /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

        /* =================== CUSTOM KEYS ============================= */

	{ MODKEY,                       XK_q,      killclient,     {0} },

        /* Audio */
	{ 0, 				XF86XK_AudioPlay, 		spawn, 	SHCMD("mpc toggle") },
	{ 0, 				XF86XK_AudioStop, 		spawn, 	SHCMD("mpc stop") },
	{ 0, 				XF86XK_AudioPause, 		spawn, 	SHCMD("mpc toggle") },
	{ 0, 				XF86XK_AudioNext, 		spawn, 	SHCMD("mpc next") },
	{ 0, 				XF86XK_AudioPrev, 		spawn, 	SHCMD("mpc prev") },
	{ 0, 				XF86XK_AudioMedia, 		spawn, 	SHCMD(TERMINAL " -e ncmpcpp") },
	{ MODKEY|ShiftMask,		XK_m, 		 		spawn, 	SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, 				XF86XK_AudioRaiseVolume, 	spawn, 	SHCMD("sound up") },
	{ 0, 				XF86XK_AudioLowerVolume, 	spawn, 	SHCMD("sound down") },

        /* Misc */
	{ 0, 				XF86XK_Mail, 			spawn, 	SHCMD(TERMINAL " -e neomutt") },
	{ 0, 				XF86XK_Calculator, 		spawn, 	SHCMD(TERMINAL " -e bc") },
	{ 0, 				XF86XK_Explorer, 		spawn, 	SHCMD(TERMINAL "-e ranger") },
	{ MODKEY, 			XK_e, 				spawn, 	SHCMD("emotes") },
	{ MODKEY, 			XK_d, 				spawn, 	SHCMD("j4-dmenu-desktop") },

        /* Brightness */
	{ 0, 				XF86XK_MonBrightnessUp, 	spawn, 	SHCMD("light 5") },
	{ 0, 				XF86XK_MonBrightnessDown, 	spawn, 	SHCMD("light -5") },

        /* Screen capture */
	{ MODKEY|ShiftMask, 		XK_a,				spawn,	SHCMD("screenshot") },
	{ MODKEY|ShiftMask,	 	XK_s,				spawn,	SHCMD("screenshot -s") },
	{ MODKEY|ShiftMask, 		XK_r, 				spawn,	SHCMD("record") },
	{ MODKEY|ShiftMask,		XK_l, 				spawn,	SHCMD("slock") },
        /* Power */
	{ 0, 				XF86XK_PowerOff, 		spawn, 	SHCMD("poweroff") },

        /* =================== END CUSTOM KEYS ============================= */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

