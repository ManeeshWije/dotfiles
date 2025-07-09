local wezterm = require("wezterm")
local act = wezterm.action
local config = wezterm.config_builder()

local sessionizer = wezterm.plugin.require("https://github.com/ElCapitanSponge/sessionizer.wezterm")

local projects = {
    "~",
    "~/projects",
    "~/Documents",
    "~/Documents/uni/*",
    "~/workspace",
}

config.font = wezterm.font("IosevkaTerm Nerd Font")
config.font_size = 12
config.color_scheme = "Black Metal (Gorgoroth) (base16)"
config.default_cursor_style = "BlinkingBlock"
config.animation_fps = 1
config.cursor_blink_ease_in = "Constant"
config.cursor_blink_ease_out = "Constant"
config.harfbuzz_features = { "calt=0", "clig=0", "liga=0" }
config.tab_bar_at_bottom = true
config.scrollback_lines = 10000
config.use_fancy_tab_bar = true
config.window_padding = {
    left = 4,
    right = 4,
    top = 4,
    bottom = 4,
}
config.window_decorations = "RESIZE"

config.window_frame = {
    font = wezterm.font({ family = "Iosevka Nerd Font", weight = "Bold" }),
    font_size = 12.0,
    active_titlebar_bg = "#000000",
    inactive_titlebar_bg = "#000000",
}

config.leader = { key = 'a', mods = 'CTRL', timeout_milliseconds = 2000 }
config.keys = {
    { key = "l",         mods = "SUPER",        action = wezterm.action.ShowLauncher },

    { key = "-",         mods = "LEADER",       action = act.SplitVertical({ domain = "CurrentPaneDomain" }) },
    { key = "\\",        mods = "LEADER",       action = act.SplitHorizontal({ domain = "CurrentPaneDomain" }) },
    { key = "h",         mods = "LEADER",       action = act.ActivatePaneDirection("Left") },
    { key = "j",         mods = "LEADER",       action = act.ActivatePaneDirection("Down") },
    { key = "k",         mods = "LEADER",       action = act.ActivatePaneDirection("Up") },
    { key = "l",         mods = "LEADER",       action = act.ActivatePaneDirection("Right") },
    { key = "x",         mods = "LEADER",       action = act.CloseCurrentPane({ confirm = true }) },
    { key = "z",         mods = "LEADER",       action = act.TogglePaneZoomState },
    { key = "o",         mods = "LEADER",       action = act.RotatePanes("Clockwise") },

    { key = "c",         mods = "LEADER",       action = act.SpawnTab("CurrentPaneDomain") },
    { key = "w",         mods = "LEADER",       action = act.CloseCurrentTab({ confirm = true }) },
    { key = "p",         mods = "LEADER",       action = act.ActivateTabRelative(-1) },
    { key = "n",         mods = "LEADER",       action = act.ActivateTabRelative(1) },

    { key = "1",         mods = "LEADER",       action = act.ActivateTab(0) },
    { key = "2",         mods = "LEADER",       action = act.ActivateTab(1) },
    { key = "3",         mods = "LEADER",       action = act.ActivateTab(2) },
    { key = "4",         mods = "LEADER",       action = act.ActivateTab(3) },
    { key = "5",         mods = "LEADER",       action = act.ActivateTab(4) },
    { key = "6",         mods = "LEADER",       action = act.ActivateTab(5) },
    { key = "7",         mods = "LEADER",       action = act.ActivateTab(6) },
    { key = "8",         mods = "LEADER",       action = act.ActivateTab(7) },
    { key = "9",         mods = "LEADER",       action = act.ActivateTab(-1) },


    { key = "[",         mods = "LEADER",       action = act.ActivateCopyMode },
    { key = "UpArrow",   mods = "SHIFT",        action = act.ScrollByLine(-1) },
    { key = "DownArrow", mods = "SHIFT",        action = act.ScrollByLine(1) },
    { key = "PageUp",    mods = "NONE",         action = act.ScrollByPage(-1) },
    { key = "PageDown",  mods = "NONE",         action = act.ScrollByPage(1) },
}

sessionizer.set_projects(projects)
sessionizer.configure(config)

return config
