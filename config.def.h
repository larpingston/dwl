
//
// my custom DWL build :)
//


// ------------------------------------------------------------
//  color helpers  (dont edit)
// ------------------------------------------------------------

#define COLOR(hex)  { ((hex>>24)&0xFF)/255.0f, ((hex>>16)&0xFF)/255.0f, \
                      ((hex>>8) &0xFF)/255.0f, (hex&0xFF)/255.0f }
#define HEX(rgb)    ((uint32_t)(rgb) << 8 | 0xFF)
#define _H(c)       ((unsigned)((c)>='0'&&(c)<='9'?(c)-'0': \
                     (c)>='a'&&(c)<='f'?(c)-'a'+10: \
                     (c)>='A'&&(c)<='F'?(c)-'A'+10:0))
#define CSS(s)      HEX((_H((s)[1])<<20)|(_H((s)[2])<<16)|(_H((s)[3])<<12)| \
		(_H((s)[4])<<8) |(_H((s)[5])<<4) | _H((s)[6]))


// ------------------------------------------------------------
//  general colors
// ------------------------------------------------------------

#define normal_border   "#444444"
#define selected_border "#c3dbe8"
#define urgent_border   "#770000"

#define desktop_bg      "#000000"
#define overlay_bg      "#000000"

// ------------------------------------------------------------
//  bar colors
// ------------------------------------------------------------

#define normal_text     "#bbbbbb"
#define normal_bg       "#181818"

#define selected_text   "#eeeeee"
#define selected_bg     "#6e838d"

#define urgent_text     "#000000"
#define urgent_bg       "#ff4444"



//  general defalt colors dwm

// normal_border   "#444444"
// selected_border "#005577"
// urgent_border   "#770000"
// desktop_bg      "#000000"
// overlay_bg      "#000000"

//  bar default colors dwm

// normal_text     "#bbbbbb"
// normal_bg       "#222222"
// selected_text   "#eeeeee"
// selected_bg     "#005577"
// urgent_text     "#000000"
// urgent_bg       "#ff4444"


static uint32_t colors[][3] = {
	[SchemeNorm] = { CSS(normal_text),   CSS(normal_bg),   CSS(normal_border)   },
	[SchemeSel]  = { CSS(selected_text), CSS(selected_bg), CSS(selected_border) },
	[SchemeUrg]  = { CSS(urgent_text),   CSS(urgent_bg),   CSS(urgent_border)   },
};
static const float rootcolor[]     = COLOR(CSS(desktop_bg));
static const float fullscreen_bg[] = COLOR(CSS(overlay_bg));


// ------------------------------------------------------------
//  general
// ------------------------------------------------------------

static const int   sloppyfocus               = 1;  // focus follows mouse
static const int   bypass_surface_visibility = 0;
static const int   borderpx                  = 1;
static const char *fonts[]                   = { "Terminus:size=13" };
static int         log_level                 = WLR_ERROR;


// ------------------------------------------------------------
//  resize
// ------------------------------------------------------------

static const float resize_mfact_step = 0.05f; // horizontal split step (Super+Left/Right)
static const float resize_cfact_step = 0.25f; // vertical weight step  (Super+Up/Down)


// ------------------------------------------------------------
//  gaps
// ------------------------------------------------------------

static int       enable_gaps = 1;
static int       gap_inner   = 6;   // between windows
static int       gap_outer   = 10;  // screen edges
static const int smartgaps   = 0;   // 1 = no gaps when only one window


// ------------------------------------------------------------
//  bar
// ------------------------------------------------------------

static const int   showbar       = 1;
static const int   topbar        = 1;
static const int   showtitle     = 0;

static const int   bargaps_left  = 12;
static const int   bargaps_right = 12;
static const int   bargaps_top   = 6;
static const int   bar_padding   = 2;


// ------------------------------------------------------------
//  tags
// ------------------------------------------------------------

static char *tags[] = { "I", "II", "III", "IV", "V", "VI" };


// ------------------------------------------------------------
//  status bar
// ------------------------------------------------------------

#define STATUS_INTERVAL 1000

static const StatusBlock status_blocks[] = {
	/* function       format                 argument                                                    interval(s) */
	{ run_command, "  󰕾 %s  | ",  "wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{printf \"%d%%\", $2*100}'",     1  },
	{ cpu_perc,    " 󰍛 %s%%  | ", NULL,                                                                          1  },
	{ run_command, " 󰘚 %s  | ",   "free -h | awk '/^Mem/ { print $3 }' | sed 's/i//g'",                          5  },
	{ datetime,    " 󰃰 %s ",    "%H:%M",                                                                       60 },
};


// ------------------------------------------------------------
//  autostart
// ------------------------------------------------------------

static const char *const autostart[] = {
	"awww-daemon", NULL,
	"/bin/sh", "-c", "wayvibes ~/wayvibes/soundpacks/nk-cream", NULL,
	"dbus-update-activation-environment", "WAYLAND_DISPLAY", "XDG_CURRENT_DESKTOP=wlroots", NULL,
	NULL
};


// ------------------------------------------------------------
//  window rules  { app_id, title, tags_mask, isfloating, monitor }
// ------------------------------------------------------------

static const Rule rules[] = {
	{ NULL, NULL, 0, 0, -1 },
};


// ------------------------------------------------------------
//  tearing
// ------------------------------------------------------------

static int tearing_allowed = 1;

// ------------------------------------------------------------
//  layouts
// ------------------------------------------------------------

static const Layout layouts[] = {
	{ "[T]", tile },
	{ "[F]", NULL }, 
	{ "[D]", dwindle },
};


// ------------------------------------------------------------
//  monitors  { name, mfact, nmaster, scale, layout, transform, x, y }
// ------------------------------------------------------------

static const MonitorRule monrules[] = {
	{ NULL, 0.55f, 1, 1, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1 },
};


// ------------------------------------------------------------
//  keyboard
// ------------------------------------------------------------

static const struct xkb_rule_names xkb_rules = {
	.options = NULL,
};
static const int repeat_rate  = 25;
static const int repeat_delay = 600;


// ------------------------------------------------------------
//  trackpad
// ------------------------------------------------------------

static const int tap_to_click            = 1;
static const int tap_and_drag            = 1;
static const int drag_lock               = 1;
static const int natural_scrolling       = 0;
static const int disable_while_typing    = 1;
static const int left_handed             = 0;
static const int middle_button_emulation = 0;

static const enum libinput_config_scroll_method  scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method   click_method  = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t                            send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile  accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double                              accel_speed   = 0.0;
static const enum libinput_config_tap_button_map button_map    = LIBINPUT_CONFIG_TAP_MAP_LRM;


// ------------------------------------------------------------
//  keybindings
// ------------------------------------------------------------

#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                                      KEY,  view,       {.ui = 1<<TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,                    KEY,  toggleview, {.ui = 1<<TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT,                   SKEY, tag,        {.ui = 1<<TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, SKEY, toggletag,  {.ui = 1<<TAG} }




#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char *termcmd[]          = { "foot", NULL };

// default wmenu colors to match dwm colors
// static const char *menucmd[] = { "wmenu-run", "-l", "10", "-f", "Terminus 12", NULL };

static const char *menucmd[] = { "wmenu-run", "-l", "10", "-f", "Terminus 13", "-N", "181818", "-n", "bbbbbb", "-S", "6e838d", "-s", "eeeeee", NULL };
static const char *filecmd[]          = { "thunar", NULL };
static const char *webcmd[]           = { "brave", NULL };
static const char *screenshotcmd[]    = { "/bin/sh", "-c", "grim - | wl-copy", NULL };
static const char *screenshotregcmd[] = { "/bin/sh", "-c", "grim -g \"$(slurp)\" - | wl-copy", NULL };
static const char *pulsemixercmd[] = { "foot", "pulsemixer", NULL };
static const char *emojicmd[]     = { "/bin/sh", "-c", "~/.config/emoji-pick", NULL };

static const Key keys[] = {
	// spawn
	{ MODKEY,                    XKB_KEY_space,      spawn,            {.v = menucmd}          },
	{ MODKEY,                    XKB_KEY_period,     spawn,            {.v = emojicmd}         },
	{ MODKEY,                    XKB_KEY_p,          spawn,            {.v = pulsemixercmd}    },
	{ MODKEY,                    XKB_KEY_w,          spawn,            {.v = webcmd}           },
	{ MODKEY,                    XKB_KEY_q,          spawn,            {.v = termcmd}          },
	{ MODKEY,                    XKB_KEY_e,          spawn,            {.v = filecmd}          },
	{ 0,                         XKB_KEY_Print,      spawn,            {.v = screenshotcmd}    },
	{ WLR_MODIFIER_CTRL,         XKB_KEY_Print,      spawn,            {.v = screenshotregcmd} },
	// gaps
	{ WLR_MODIFIER_ALT,          XKB_KEY_p,          togglegaps,       {0}                     },
	{ WLR_MODIFIER_ALT,          XKB_KEY_i,          incgaps,          {.i = -6}               },
	{ WLR_MODIFIER_ALT,          XKB_KEY_o,          incgaps,          {.i = +6}               },
	// windows
	{ MODKEY,                    XKB_KEY_j,          focusstack,       {.i = +1}               },
	{ MODKEY,                    XKB_KEY_k,          focusstack,       {.i = -1}               },
	{ MODKEY,                    XKB_KEY_h,          setmfact,         {.f = -0.05f}           },
	{ MODKEY,                    XKB_KEY_l,          setmfact,         {.f = +0.05f}           },
	{ MODKEY,                    XKB_KEY_Left,       setmfact,         {.f = -resize_mfact_step} },
	{ MODKEY,                    XKB_KEY_Right,      setmfact,         {.f = +resize_mfact_step} },
	{ MODKEY,                    XKB_KEY_Up,         setcfact,         {.f = -resize_cfact_step} },
	{ MODKEY,                    XKB_KEY_Down,       setcfact,         {.f = +resize_cfact_step} },
	{ MODKEY,                    XKB_KEY_Return,     zoom,             {0}                     },
	{ MODKEY,                    XKB_KEY_c,          killclient,       {0}                     },
	{ MODKEY,                    XKB_KEY_v,          togglefloating,   {0}                     },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     togglefullscreen, {0}                     },
	// layout
	{ MODKEY,                    XKB_KEY_t,          setlayout,        {.v = &layouts[0]}      },
	{ MODKEY,                    XKB_KEY_f,          setlayout,        {.v = &layouts[1]}      },
	{ MODKEY,                    XKB_KEY_d,          setlayout,        {.v = &layouts[2]}      },
	// tags
	{ MODKEY,                    XKB_KEY_Tab,        view,             {0}                     },
	{ MODKEY,                    XKB_KEY_0,          view,             {.ui = ~0}              },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,              {.ui = ~0}              },
	TAGKEYS(XKB_KEY_1, XKB_KEY_exclam,      0),
	TAGKEYS(XKB_KEY_2, XKB_KEY_at,          1),
	TAGKEYS(XKB_KEY_3, XKB_KEY_numbersign,  2),
	TAGKEYS(XKB_KEY_4, XKB_KEY_dollar,      3),
	TAGKEYS(XKB_KEY_5, XKB_KEY_percent,     4),
	TAGKEYS(XKB_KEY_6, XKB_KEY_asciicircum, 5),
	TAGKEYS(XKB_KEY_7, XKB_KEY_ampersand,   6),
	TAGKEYS(XKB_KEY_8, XKB_KEY_asterisk,    7),
	TAGKEYS(XKB_KEY_9, XKB_KEY_parenleft,   8),
	// monitors
	{ MODKEY,                    XKB_KEY_comma,      focusmon,         {.i = WLR_DIRECTION_LEFT}  },
	{ MODKEY,                    XKB_KEY_semicolon,  focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,           {.i = WLR_DIRECTION_LEFT}  },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_colon,      tagmon,           {.i = WLR_DIRECTION_RIGHT} },
	// bar
	{ MODKEY,                    XKB_KEY_b,          togglebar,        {0}                     },
	// quit
	{ MODKEY,                             XKB_KEY_m,                quit, {0} },
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, XKB_KEY_Terminate_Server, quit, {0} },
	// virtual terminals
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, XKB_KEY_XF86Switch_VT_##n, chvt, {.ui=(n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};


// ------------------------------------------------------------
//  mouse buttons
// ------------------------------------------------------------

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,     {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,     {.v = &layouts[1]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0}                },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd}     },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove}    },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0}                },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize}  },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0}                },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0}                },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0}                },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0}                },
};

