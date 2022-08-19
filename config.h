/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 2;     /* border pixel of windows */
static const unsigned int snap        = 12;    /* snap pixel */
static const int          vertpad     = 12;    /* vertical padding of bar */
static const int          sidepad     = 12;    /* horizontal padding of bar */
static const int          horizpadbar = 10;     /* horizontal padding for
                                                  statusbar */
static const int          vertpadbar  = 10;     /* vertical padding for
                                                  statusbar */
static const unsigned int gappx       = 12;    /* gaps between windows */

static const int          showbar     = 1;     /* 0 means no bar */
static const int          topbar      = 1;     /* 0 means bottom bar */
static const unsigned int colorfultag = 1;     /* 0 means use SchemeSel for
                                                     selected tag */

static const char *fonts[] = { "Victor Mono SemiBold:size=12:antialias=true:autohint=true" };

static const char col_bg[]     = "#232326";
static const char col_bg2[]    = "#2c2d31";
static const char col_fg[]     = "#a7aab0";
static const char col_red[]    = "#de5d68";
static const char col_green[]  = "#8fb573";
static const char col_yellow[] = "#dbb671";
static const char col_blue[]   = "#57a5e5";
static const char col_purple[] = "#bb70d2";
static const char col_cyan[]   = "#51a8b3";
static const char col_grey[]   = "#818387";

static const char *colors[][3] = {
    /*                   fg          bg      border   */
    [SchemeNorm]     = { col_fg,     col_bg,  col_grey },
    [SchemeSel]      = { col_fg,     col_bg2, col_cyan  },

    [SchemeTag]      = { col_grey,   col_bg,  NULL },
    [SchemeTag1]     = { col_red,    col_bg,  NULL },
    [SchemeTag2]     = { col_green,  col_bg,  NULL },
    [SchemeTag3]     = { col_blue,   col_bg,  NULL },
    [SchemeTag4]     = { col_yellow, col_bg,  NULL },
};

/* tagging */
static const char *tags[]      = { "I", "II", "III", "IV" };
static const int  tagschemes[] = { SchemeTag1, SchemeTag2, SchemeTag3,
                                   SchemeTag4 };

static const unsigned int ulinepad      = 5;    /* horizontal padding between
                                                   the underline and tag */
static const unsigned int ulinestroke   = 2;    /* thickness / height of the
                                                   underline */
static const unsigned int ulinevoffset  = 0;    /* how far above the bottom of
                                                   the bar the line should appear */
static const int          ulineall      = 0;    /* 1 to show underline on all
                                                   tags, 0 for just the active ones */

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
 	{ "[\\]",      dwindle },    /* first entry is default */
    { "><>",      NULL },        /* no layout function means floating behavior */
    { "[]=",      tile },
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
#define TERMINAL_CMD       "st"
#define LAUNCHER_CMD       "dmenu_run"
#define BROWSER_CMD        "qutebrowser"
#define LOCKSCREEN_CMD     "slock"
#define SCREENSHOT_CMD     "scrot -z '%Y-%m-%d_$wx$h.png' -e 'mv $f $HOME/pics'"
#define LOCKSCREEN_ON_CMD  "igns on"
#define LOCKSCREEN_OFF_CMD "igns off"
#define INCREASE_BRIGHTNESS_CMD "xbacklight -inc 10"
#define DECREASE_BRIGHTNESS_CMD "xbacklight -dec 10"

#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier           key        function        argument */
    { MODKEY,             XK_d,      spawn,          SHCMD( LAUNCHER_CMD ) },
    { MODKEY,             XK_z,      spawn,          SHCMD( TERMINAL_CMD ) },
    { MODKEY|ControlMask, XK_b,      spawn,          SHCMD( BROWSER_CMD ) },
    { MODKEY,             XK_l,      spawn,          SHCMD( LOCKSCREEN_CMD ) },
    { MODKEY,             XK_Print,  spawn,          SHCMD( SCREENSHOT_CMD ) },
    { MODKEY,             XK_F1,     spawn,          SHCMD( LOCKSCREEN_ON_CMD ) },
    { MODKEY,             XK_F2,     spawn,          SHCMD( LOCKSCREEN_OFF_CMD ) },
    { MODKEY,             XK_F5,     spawn,          SHCMD( DECREASE_BRIGHTNESS_CMD ) },
    { MODKEY,             XK_F6,     spawn,          SHCMD( INCREASE_BRIGHTNESS_CMD ) },

    { MODKEY,             XK_b,      togglebar,      {0} },
    { MODKEY,             XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,             XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,             XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,             XK_p,      incnmaster,     {.i = -1 } },
    { MODKEY,             XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,             XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,   XK_h,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,   XK_l,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,   XK_o,      setcfact,       {.f =  0.00} },
    { MODKEY,             XK_Return, zoom,           {0} },
    { MODKEY,             XK_Tab,    view,           {0} },
    { MODKEY,             XK_x,      killclient,     {0} },
	{ MODKEY,             XK_r,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,             XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,             XK_t,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,             XK_m,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,             XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,   XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,   XK_f,      togglefullscr,  {0} },
    { MODKEY,             XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,   XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,             XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,             XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,   XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,   XK_period, tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,   XK_q,      quit,           {0} },

    TAGKEYS(              XK_1,                      0)
    TAGKEYS(              XK_2,                      1)
    TAGKEYS(              XK_3,                      2)
    TAGKEYS(              XK_4,                      3)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask        button          function        argument */
    { ClkLtSymbol,          0,                Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,                Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkStatusText,        0,                Button2,        spawn,          {.v = TERMINAL_CMD } },
    { ClkClientWin,         MODKEY,           Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,           Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,           Button3,        resizemouse,    {0} },
    { ClkClientWin,         MODKEY|ShiftMask, Button1,        dragmfact,      {0} },
    { ClkClientWin,         MODKEY|ShiftMask, Button2,        dragcfact,      {0} },
    { ClkTagBar,            0,                Button1,        view,           {0} },
    { ClkTagBar,            0,                Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,           Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,           Button3,        toggletag,      {0} },
};

