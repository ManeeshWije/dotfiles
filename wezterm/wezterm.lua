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
    font = wezterm.font({ family = "IosevkaTerm Nerd Font", weight = "Bold" }),
    font_size = 12.0,
    active_titlebar_bg = "#000000",
    inactive_titlebar_bg = "#000000",
}

config.keys = {
    -- Launcher & copy mode
    { key = "l",         mods = "ALT",       action = wezterm.action.ShowLauncher },
    { key = "[",         mods = "ALT",       action = act.ActivateCopyMode },

    -- Scroll
    { key = "UpArrow",   mods = "SHIFT",     action = act.ScrollByLine(-1) },
    { key = "DownArrow", mods = "SHIFT",     action = act.ScrollByLine(1) },
    { key = "PageUp",    mods = "NONE",      action = act.ScrollByPage(-1) },
    { key = "PageDown",  mods = "NONE",      action = act.ScrollByPage(1) },

    -- Sessionizer
    { key = "s",         mods = "ALT",       action = sessionizer.switch_workspace() },

    -- Tabs
    { key = "t",         mods = "ALT",       action = act.SpawnTab("CurrentPaneDomain") },       -- new tab
    { key = "w",         mods = "ALT",       action = act.CloseCurrentTab({ confirm = true }) }, -- close tab
    { key = "Tab",       mods = "ALT",       action = act.ActivateTabRelative(1) },              -- next tab
    { key = "Tab",       mods = "ALT|SHIFT", action = act.ActivateTabRelative(-1) },             -- prev tab
    { key = "1",         mods = "ALT",       action = act.ActivateTab(0) },
    { key = "2",         mods = "ALT",       action = act.ActivateTab(1) },
    { key = "3",         mods = "ALT",       action = act.ActivateTab(2) },
    { key = "4",         mods = "ALT",       action = act.ActivateTab(3) },
    { key = "5",         mods = "ALT",       action = act.ActivateTab(4) },
    { key = "6",         mods = "ALT",       action = act.ActivateTab(5) },
    { key = "7",         mods = "ALT",       action = act.ActivateTab(6) },
    { key = "8",         mods = "ALT",       action = act.ActivateTab(7) },
    { key = "9",         mods = "ALT",       action = act.ActivateTab(-1) }, -- last tab

    -- Panes
    { key = "\\",        mods = "ALT",       action = act.SplitHorizontal({ domain = "CurrentPaneDomain" }) },
    { key = "-",        mods = "ALT",       action = act.SplitVertical({ domain = "CurrentPaneDomain" }) },
    { key = "h",         mods = "ALT",       action = act.ActivatePaneDirection("Left") },
    { key = "j",         mods = "ALT",       action = act.ActivatePaneDirection("Down") },
    { key = "k",         mods = "ALT",       action = act.ActivatePaneDirection("Up") },
    { key = "l",         mods = "ALT",       action = act.ActivatePaneDirection("Right") },
    { key = "q",         mods = "ALT",       action = act.CloseCurrentPane({ confirm = true }) },

    -- Reload config
    { key = "r",         mods = "ALT|SHIFT", action = act.ReloadConfiguration },
}

sessionizer.set_projects(projects)
sessionizer.configure(config)

return config
