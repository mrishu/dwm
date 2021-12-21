/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int gappx     = 5;        /* gaps between windows */
static unsigned int snap      = 32;       /* snap pixel */

static const unsigned int baralpha = 255;
static const unsigned int borderalpha = OPAQUE;

static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */

static int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static char font[]            = "JetBrains Mono:size=11:style=Bold";
static char dmenufont[]       = "JetBrainsMono Nerd Font:size=11";
static const char *fonts[]          = { font, "Feather:size=15", "JetBrainsMono Nerd Font:size=15" };

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";

static char tagnormbgcolor[]        = "#222222";
static char tagnormfgcolor[]        = "#bbbbbb";
static char tagselbgcolor[]         = "#005577";
static char tagselfgcolor[]         = "#eeeeee";
static char tagoccbgcolor[]         = "#222222";
static char tagoccfgcolor[]         = "#005577";

static char infonormbgcolor[]       = "#222222";
static char infonormfgcolor[]       = "#bbbbbb";
static char infoselfgcolor[]        = "#eeeeee";
static char infoselbgcolor[]        = "#005577";

static char col_red[]          = "#ff0000";
static char col_green[]        = "#00ff00";
static char col_yellow[]       = "#ffff00";
static char col_blue[]         = "#0000ff";
static char col_magenta[]      = "#ff00ff";
static char col_cyan[]         = "#00ffff";
static char col_white[]        = "#ffffff";

static char *colors[][3]      = {
	/*					fg         bg          border   */
	[SchemeRed] = { col_red, normbgcolor,    "#000000" },         // \x01
	[SchemeGreen] = { col_green, normbgcolor,    "#000000" },     // \x02
	[SchemeYellow] =	 { col_yellow, normbgcolor, "#000000" },  // \x03
	[SchemeBlue] =	 { col_blue, normbgcolor, "#000000" },        // \x04
    [SchemeMagenta] = { col_magenta, normbgcolor, "#000000" },    // \x05
    [SchemeCyan] = { col_cyan, normbgcolor, "#000000" },          // \x05
    
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor }, // \x07
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  }, // \x08
    
    [SchemeTagsNorm]  = { tagnormfgcolor, tagnormbgcolor, "#000000" },
	[SchemeTagsSel]  = { tagselfgcolor, tagselbgcolor, "#000000" },
	[SchemeTagsOcc]  = { tagoccfgcolor, tagoccbgcolor, "#000000" },
    
    [SchemeInfoNorm]  = { infonormfgcolor, infonormbgcolor, "#000000" },
    [SchemeInfoSel]  = { infoselfgcolor, infoselbgcolor, "#000000" },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeRed] = { OPAQUE, baralpha, borderalpha },
	[SchemeGreen] = { OPAQUE, baralpha, borderalpha },
	[SchemeYellow] = { OPAQUE, baralpha, borderalpha },
	[SchemeBlue] =	 { OPAQUE, baralpha, borderalpha },
    [SchemeMagenta] = { OPAQUE, baralpha, borderalpha },
    [SchemeCyan] = { OPAQUE, baralpha, borderalpha },
    
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
    
    [SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsOcc]  = { OPAQUE, baralpha, borderalpha },
    
    [SchemeInfoNorm]  = { OPAQUE, baralpha, borderalpha },
    [SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/* { "Gimp",     NULL,       NULL,       0,            1,           -1 }, */
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
    { "discord",   NULL,     NULL,          1 << 3,             0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-c", "-l", "20", "-p", "Launch", NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
        
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
        
		{ "tagnormbgcolor",        STRING,  &tagnormbgcolor },
		{ "tagnormfgcolor",        STRING,  &tagnormfgcolor },
		{ "tagselbgcolor",         STRING,  &tagselbgcolor },
		{ "tagselfgcolor",         STRING,  &tagselfgcolor },
		{ "tagoccbgcolor",         STRING,  &tagoccbgcolor },
		{ "tagoccfgcolor",         STRING,  &tagoccfgcolor },
        
		{ "infonormbgcolor",        STRING,  &infonormbgcolor },
		{ "infonormfgcolor",        STRING,  &infonormfgcolor },
		{ "infoselbgcolor",         STRING,  &infoselbgcolor },
		{ "infoselfgcolor",         STRING,  &infoselfgcolor },
        
        { "col_red",            STRING,  &col_red },
        { "col_yellow",         STRING,  &col_yellow },
        { "col_green",          STRING,  &col_green },
        { "col_blue",           STRING,  &col_blue },
        { "col_magenta",        STRING,  &col_magenta },
        { "col_cyan",           STRING,  &col_cyan },
        { "col_white",          STRING,  &col_white },
        
		{ "borderpx",          	INTEGER, &borderpx },
        { "gappx",              INTEGER, &gappx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_i,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	// { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	// { MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
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

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            quit,      {0} },
	{ 2,            quit,      {1} },
};
