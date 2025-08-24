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
    { key = "l",         mods = "SUPER", action = act.ShowLauncher },
    { key = "[",         mods = "SUPER", action = act.ActivateCopyMode },

    { key = "UpArrow",   mods = "SHIFT", action = act.ScrollByLine(-1) },
    { key = "DownArrow", mods = "SHIFT", action = act.ScrollByLine(1) },
    { key = "PageUp",    mods = "NONE",  action = act.ScrollByPage(-1) },
    { key = "PageDown",  mods = "NONE",  action = act.ScrollByPage(1) },

    { key = "s",         mods = "SUPER", action = sessionizer.switch_workspace() },
}

sessionizer.set_projects(projects)
sessionizer.configure(config)

return config
