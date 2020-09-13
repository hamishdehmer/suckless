/* See LICENSE file for copyright and license details. */

//////////////////
//    Layout    //
//////////////////

static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const unsigned int gappx     = 18;        /* gaps between windows */
static const int topbar             = 0;        /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int attachdirection = 4;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */


/////////////////
//    Fonts    //
/////////////////

// dwm
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:size=12",
					"Noto Color Emoji:size=12",
					"Font Awesome 5 Brands:size=14",
					"Font Awesome 5 Free:size=14",
					"FontAwesome:size=14"};
// dmenu
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=12";

//////////////////////////
//    Color Scheming    //
//////////////////////////

// Theme
static const char bg[]       = "#2a2426"; // Background
static const char ib[]       = "#e68183"; // Inactive Border
static const char ft[]       = "#e6d6ac"; // Font
static const char tc[]       = "#242021"; // Current Tag & Window Font Color
static const char ab[]       = "#87af87"; // Top Bar Second Color & Active Border

// Color Layout
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { ft, 	    bg,        ib },
	[SchemeSel]  = { tc,        ab,        ab  },
};

////////////////
//    Tags    //
////////////////

static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

/////////////////////////
//    Window Rules     //
/////////////////////////

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 }
};

//////////////////
//    Layout    //
//////////////////

// Layout Specifications
static const float mfact     = 0.51; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

// Layouts
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",      dwindle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
};

//////////////////////////////////
//    Binding Configurations    //
//////////////////////////////////

// Key Definitions
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// Commands //

// Window Commands
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bg, "-nf", ft, "-sb", ab, "-sf", tc, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *browser[]  = { "brave", NULL };
static const char *fbrowser[] = { "nemo", NULL };
static const char *slock[]    = { "slock", NULL };

// Volume Commands
static const char *upvol[]   = { "amixer", "-q", "sset", "Master", "2%+", NULL };
static const char *downvol[] = { "amixer", "-q", "sset", "Master", "2%-", NULL };
static const char *mutevol[] = { "amixer", "-q", "sset", "Master", "0%",  NULL };

// Restart Pulse
static const char *killpulse[] = { "pulseaudio", "-k", NULL };
static const char *startpulse[] = { "pulseaudio", "-D", NULL };

// Keyboard Bindings
#include "push.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browser } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_n,      spawn,          {.v = fbrowser } },
        { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
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
        { MODKEY,                       XK_F2, 	   spawn,          {.v = downvol } },
  	{ MODKEY,                       XK_F1,     spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = upvol   } },
	{ MODKEY|ShiftMask,             XK_bracketleft, spawn,     {.v = killpulse } },
	{ MODKEY|ShiftMask,             XK_bracketright, spawn,    {.v = startpulse } },
	{ MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
	{ MODKEY|ControlMask,           XK_k,      pushup,         {0} },
};

// Mouse Bindings
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

/* quitting */
static const int EMPTY_WINDOW_COUNT = 30;
