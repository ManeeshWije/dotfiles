local colors = {
	base00 = "#000000",
	base01 = "#121212",
	base02 = "#222222",
	base03 = "#333333",
	base04 = "#999999",
	base05 = "#c1c1c1",
	base06 = "#999999",
	base07 = "#c1c1c1",
	base08 = "#5f8787",
	base09 = "#aaaaaa",
	base0A = "#8c7f70",
	base0B = "#9b8d7f",
	base0C = "#aaaaaa",
	base0D = "#888888",
	base0E = "#999999",
	base0F = "#444444",
}

local function black_metal()
	vim.cmd("highlight clear")
	vim.o.background = "dark"

	local hl = vim.api.nvim_set_hl

	hl(0, "Normal", { fg = colors.base05, bg = "NONE" })
	hl(0, "NormalNC", { fg = colors.base05, bg = "NONE" })
	hl(0, "NormalFloat", { fg = colors.base05, bg = colors.base01 })
	hl(0, "FloatBorder", { fg = colors.base03, bg = colors.base01 })

	hl(0, "CursorLine", { bg = colors.base01 })
	hl(0, "LineNr", { fg = colors.base03 })
	hl(0, "CursorLineNr", { fg = colors.base04, bold = true })
	hl(0, "Visual", { bg = colors.base02 })

	hl(0, "Comment", { fg = colors.base03, italic = true })
	hl(0, "String", { fg = colors.base0B })
	hl(0, "Number", { fg = colors.base09 })
	hl(0, "Boolean", { fg = colors.base09 })
	hl(0, "Identifier", { fg = colors.base08 })
	hl(0, "Function", { fg = colors.base0D })
	hl(0, "Keyword", { fg = colors.base0E })
	hl(0, "Operator", { fg = colors.base05 })
	hl(0, "Type", { fg = colors.base0A })
	hl(0, "Special", { fg = colors.base0C })
	hl(0, "Delimiter", { fg = colors.base04 })

	hl(0, "DiagnosticError", { fg = colors.base08 })
	hl(0, "DiagnosticWarn", { fg = colors.base0A })
	hl(0, "DiagnosticInfo", { fg = colors.base0D })
	hl(0, "DiagnosticHint", { fg = colors.base0C })
end

local function system_is_dark()
	if vim.fn.has("mac") == 1 then
		local result = vim.system({
			"defaults",
			"read",
			"-g",
			"AppleInterfaceStyle",
		}, { text = true }):wait()

		return result.code == 0 and result.stdout:match("Dark") ~= nil
	end

	if vim.fn.has("unix") == 1 then
		local result = vim.system({
			"dconf",
			"read",
			"/org/gnome/desktop/interface/color-scheme",
		}, { text = true }):wait()

		return result.code == 0 and result.stdout:match("prefer%-dark") ~= nil
	end

	return true
end

local mode

local function update_theme()
	local next_mode = system_is_dark() and "dark" or "light"

	if next_mode == mode then
		return
	end

	mode = next_mode

	if mode == "dark" then
		black_metal()
	else
		vim.o.background = "light"
		vim.cmd.colorscheme("shine")
	end
end

update_theme()

vim.api.nvim_create_autocmd("FocusGained", {
	callback = update_theme,
})
