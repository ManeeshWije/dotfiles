local wezterm = require("wezterm")

local config = wezterm.config_builder()

config.font = wezterm.font 'Iosevka Nerd Font'
config.font_size = 15
config.color_scheme = 'GruvboxDarkHard'
config.enable_tab_bar = true
config.window_decorations = "RESIZE"
config.default_cursor_style = 'BlinkingBlock'
config.animation_fps = 1
config.cursor_blink_ease_in = 'Constant'
config.cursor_blink_ease_out = 'Constant'
config.keys = {
  { key = 'l', mods = 'SUPER', action = wezterm.action.ShowLauncher },
}
config.harfbuzz_features = { 'calt=0', 'clig=0', 'liga=0' }

return config
