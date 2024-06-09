local wezterm = require("wezterm")
local act = wezterm.action
local config = wezterm.config_builder()

local sessionizer = wezterm.plugin.require("https://github.com/ElCapitanSponge/sessionizer.wezterm")

local projects = {
	"~",
	"~/projects",
	"~/Documents",
	"~/Documents/uni",
}

config.font = wezterm.font("Iosevka Nerd Font")
config.font_size = 15
config.color_scheme = "GruvboxDarkHard"
config.default_cursor_style = "BlinkingBlock"
config.animation_fps = 1
config.cursor_blink_ease_in = "Constant"
config.cursor_blink_ease_out = "Constant"
config.harfbuzz_features = { "calt=0", "clig=0", "liga=0" }
config.tab_bar_at_bottom = true

config.leader = { key = "`", timeout_milliseconds = 1000 }
config.keys = {
	{ key = "l", mods = "SUPER", action = wezterm.action.ShowLauncher },
	-- Send ` when pressing ` twice
	{ key = "`", mods = "LEADER", action = act.SendKey({ key = "`" }) },

	{ key = "'", mods = "LEADER", action = act.SplitVertical({ domain = "CurrentPaneDomain" }) },
	{ key = "%", mods = "LEADER|SHIFT", action = act.SplitHorizontal({ domain = "CurrentPaneDomain" }) },
	{ key = "h", mods = "LEADER", action = act.ActivatePaneDirection("Left") },
	{ key = "j", mods = "LEADER", action = act.ActivatePaneDirection("Down") },
	{ key = "k", mods = "LEADER", action = act.ActivatePaneDirection("Up") },
	{ key = "l", mods = "LEADER", action = act.ActivatePaneDirection("Right") },
	{ key = "x", mods = "LEADER", action = act.CloseCurrentPane({ confirm = true }) },
	{ key = "z", mods = "LEADER", action = act.TogglePaneZoomState },
	{ key = "o", mods = "LEADER", action = act.RotatePanes("Clockwise") },

	{ key = "w", mods = "LEADER", action = act.ShowLauncherArgs({ flags = "FUZZY|WORKSPACES" }) },
}

sessionizer.set_projects(projects)
sessionizer.configure(config)

return config
