-- Options
vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1
vim.o.number = true
vim.o.relativenumber = true
vim.o.signcolumn = "yes"
vim.o.termguicolors = true
vim.o.wrap = false
vim.o.swapfile = false
vim.g.mapleader = ","
vim.o.winborder = "single"
vim.o.guicursor = ""
vim.o.ignorecase = true
vim.o.smartcase = true
vim.o.updatetime = 100
vim.o.timeoutlen = 300
vim.o.scrolloff = 10
vim.o.sidescrolloff = 10
vim.o.hlsearch = true
vim.o.tabstop = 4
vim.o.softtabstop = 4
vim.o.shiftwidth = 4
vim.o.expandtab = true
vim.o.smartindent = true
vim.o.previewheight = 25
vim.opt.fillchars = { fold = " " }
vim.o.foldmethod = "indent"
vim.o.foldenable = false
vim.o.foldlevel = 99
vim.o.list = false
vim.opt.listchars = { tab = "» ", trail = "·", nbsp = "␣" }
vim.g.markdown_folding = 1
vim.o.splitright = true
vim.o.splitbelow = true
vim.opt.undofile = true
vim.opt.undodir = os.getenv("HOME") .. "/.vim/undo"
vim.opt.undolevels = 1000
vim.opt.undoreload = 10000

-- Plugins
vim.pack.add({
	{ src = "https://github.com/nvim-lua/plenary.nvim" },
	{ src = "https://github.com/RRethy/base16-nvim" },
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter" },
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter-context" },
	{ src = "https://github.com/ibhagwan/fzf-lua" },
	{ src = "https://github.com/mikavilpas/yazi.nvim" },
	{ src = "https://github.com/iamcco/markdown-preview.nvim" },
	{ src = "https://github.com/stevearc/conform.nvim" },
	{ src = "https://github.com/tpope/vim-dadbod" },
	{ src = "https://github.com/kristijanhusak/vim-dadbod-ui" },
	{ src = "https://github.com/kristijanhusak/vim-dadbod-completion" },
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter-textobjects" },
	{ src = "https://github.com/neovim/nvim-lspconfig" },
	{ src = "https://github.com/christoomey/vim-tmux-navigator" },
	{ src = "https://github.com/github/copilot.vim" },
	{ src = "https://github.com/f-person/auto-dark-mode.nvim" },
	{ src = "https://github.com/linrongbin16/gitlinker.nvim" },
	{ src = "https://github.com/ThePrimeagen/harpoon", version = "harpoon2" },
	{ src = "https://github.com/akinsho/toggleterm.nvim" },
})
vim.cmd(":hi statusline guibg=NONE")
vim.cmd([[set completeopt+=menuone,noselect,popup]])
vim.cmd([[colorscheme base16-black-metal-gorgoroth]])

local all_levels = {
	vim.diagnostic.severity.ERROR,
	vim.diagnostic.severity.WARN,
	vim.diagnostic.severity.HINT,
	vim.diagnostic.severity.INFO,
}

vim.diagnostic.config({
	severity_sort = true,
	virtual_lines = false,
	signs = {
		severity = all_levels,
	},
	underline = {
		severity = all_levels,
	},
	virtual_text = {
		severity = all_levels,
	},
	float = {
		severity = all_levels,
	},
})

-- Setup plugins via require
require("fzf-lua").setup({
	keymap = {
		builtin = {
			["<C-a>"] = "select-all+accept",
			["<C-d>"] = "half-page-down",
			["<C-u>"] = "half-page-up",
			["<C-f>"] = "preview-page-down",
			["<C-b>"] = "preview-page-up",
			["<C-n>"] = "down",
			["<C-p>"] = "up",
		},
		fzf = {
			["ctrl-a"] = "select-all+accept",
			["ctrl-d"] = "half-page-down",
			["ctrl-u"] = "half-page-up",
			["ctrl-f"] = "preview-page-down",
			["ctrl-b"] = "preview-page-up",
			["ctrl-n"] = "down",
			["ctrl-p"] = "up",
		},
	},
})

require("nvim-treesitter.configs").setup({
	ensure_installed = {
		"bash",
		"c",
		"cpp",
		"css",
		"dockerfile",
		"go",
		"html",
		"javascript",
		"json",
		"lua",
		"markdown",
		"python",
		"rust",
		"sql",
		"typescript",
		"vim",
		"yaml",
		"java",
		"php",
	},
	auto_install = true,
	sync_install = false,
	highlight = { enable = true },
	indent = { enable = true },
})

require("treesitter-context").setup({
	enable = true,
})

require("conform").setup({
	notify_on_error = true,
	formatters_by_ft = {
		lua = { "stylua" },
		python = { "isort", "black" },
		javascript = { "prettier" },
		typescript = { "prettier" },
		javascriptreact = { "prettier" },
		typescriptreact = { "prettier" },
		java = { "google-java-format" },
		go = { "gofmt", "goimports" },
		rust = { "rustfmt" },
		php = { "php-cs-fixer" },
		c = { "clang-format" },
		markdown = { "prettier" },
		sql = { "sql_formatter" },
		html = { "prettier" },
	},
	formatters = {
		sql_formatter = {
			command = "sql-formatter",
			args = { "--language", "postgresql" },
		},
	},
})

require("yazi").setup({
	open_for_directories = true,
})

require("auto-dark-mode").setup({
	set_dark_mode = function()
		vim.cmd([[colorscheme base16-black-metal-gorgoroth]])
		vim.opt.background = "dark"
	end,
	set_light_mode = function()
		vim.cmd([[colorscheme base16-ayu-light]])
		vim.opt.background = "light"
	end,
	update_interval = 3000,
	fallback = "dark",
})

require("gitlinker").setup()

local harpoon = require("harpoon")
harpoon:setup()

local Terminal = require("toggleterm.terminal").Terminal
local lazygit = Terminal:new({
	cmd = "lazygit",
	hidden = true,
	direction = "float",
})
local lazydocker = Terminal:new({
	cmd = "lazydocker",
	hidden = true,
	direction = "float",
})
function _lazygit_toggle()
	lazygit:toggle()
end
function _lazydocker_toggle()
	lazydocker:toggle()
end

vim.lsp.enable({
	"gopls",
	"lua_ls",
	"ts_ls",
	"pyright",
	"clangd",
	"html",
	"cssls",
	"jsonls",
	"bashls",
	"dockerls",
	"yamlls",
	"rust_analyzer",
	"eslint",
	"tailwindcss",
	"jdtls",
	"emmet_ls",
})

-- Keymaps
-- fzf
local fzf = require("fzf-lua")
vim.keymap.set("n", "<leader>ff", fzf.files, { noremap = true, silent = true }) -- File find
vim.keymap.set("n", "<leader>fg", fzf.git_files, { noremap = true, silent = true }) -- Git file find
vim.keymap.set("n", "<leader>fb", fzf.buffers, { noremap = true, silent = true }) -- Find buffer
vim.keymap.set("n", "<leader>sg", fzf.live_grep, { noremap = true, silent = true }) -- Grep string
vim.keymap.set("n", "<leader>sm", fzf.spellcheck, { noremap = true, silent = true }) -- Misspelled words
vim.keymap.set("n", "<leader>sp", fzf.spell_suggest, { noremap = true, silent = true }) -- Suggestions for word under cursor
vim.keymap.set("n", "<leader>fh", fzf.help_tags, { noremap = true, silent = true }) -- Help tags
vim.keymap.set("n", "<leader>df", fzf.diagnostics_document, { noremap = true, silent = true }) -- Document Diagnostics

-- harpoon
vim.keymap.set("n", "<leader>a", function()
	harpoon:list():add()
end)
vim.keymap.set("n", "<leader>h", function()
	harpoon.ui:toggle_quick_menu(harpoon:list())
end)

vim.keymap.set("n", "<leader>1", function()
	harpoon:list():select(1)
end)
vim.keymap.set("n", "<leader>2", function()
	harpoon:list():select(2)
end)
vim.keymap.set("n", "<leader>3", function()
	harpoon:list():select(3)
end)
vim.keymap.set("n", "<leader>4", function()
	harpoon:list():select(4)
end)
vim.keymap.set("n", "<leader>5", function()
	harpoon:list():select(5)
end)

vim.keymap.set("n", "<C-M-H>", function()
	harpoon:list():prev()
end)
vim.keymap.set("n", "<C-M-L>", function()
	harpoon:list():next()
end)

-- terminal apps
vim.api.nvim_set_keymap("n", "<leader>lz", "<cmd>lua _lazygit_toggle()<CR>", { noremap = true, silent = true })
vim.api.nvim_set_keymap("n", "<leader>ld", "<cmd>lua _lazydocker_toggle()<CR>", { noremap = true, silent = true })

-- qol
vim.keymap.set({ "n", "x" }, "<leader>y", '"+y')
vim.keymap.set({ "n", "x" }, "<leader>yy", '"+yy')
vim.keymap.set({ "n", "x" }, "<leader>p", '"+p')
vim.keymap.set("i", "jk", "<Esc>")
vim.keymap.set("n", "<Esc>", "<cmd>nohlsearch<CR>")
vim.keymap.set("n", "<S-l>", ":bnext<CR>")
vim.keymap.set("n", "<S-h>", ":bprevious<CR>")
vim.keymap.set({ "n", "x" }, "x", '"_x')
vim.keymap.set("v", "J", ":m '>+1<CR>gv=gv")
vim.keymap.set("v", "K", ":m '<-2<CR>gv=gv")
vim.keymap.set("n", "J", "mzJ`z")
vim.keymap.set("n", "<C-d>", "<C-d>zz")
vim.keymap.set("n", "<C-u>", "<C-u>zz")
vim.keymap.set("n", "<C-H>", "<C-W>h")
vim.keymap.set("n", "<C-J>", "<C-W>j")
vim.keymap.set("n", "<C-K>", "<C-W>k")
vim.keymap.set("n", "<C-L>", "<C-W>l")
vim.keymap.set("n", "<leader>q", "<cmd>cclose<cr>", { desc = "Close quickfix list" })
vim.keymap.set("n", "<leader>c", function()
	require("conform").format({ async = true, lsp_fallback = true })
end, { desc = "Format Document" })
vim.keymap.set("n", "<leader>e", function()
	require("yazi").yazi()
end)

-- manual autocomplete
vim.keymap.set("i", "<C-space>", function()
	if vim.bo.omnifunc ~= "" then
		-- If omnifunc is set (like in SQL files), use omni-completion
		return "<C-x><C-o>"
	else
		-- Otherwise use LSP completion
		return vim.lsp.completion.get()
	end
end, { expr = true, desc = "Smart completion" })

-- Autocommands
-- remember last cursor position
vim.api.nvim_create_augroup("vimStartup", { clear = true })
vim.api.nvim_create_autocmd("BufReadPost", {
	group = "vimStartup",
	callback = function()
		local last_position = vim.fn.line([['"]])
		local last_line = vim.fn.line("$")
		local filetype = vim.bo.filetype

		if last_position >= 1 and last_position <= last_line and not filetype:match("commit") then
			vim.cmd('normal! g`"')
		end
	end,
})

-- remember folds
vim.api.nvim_create_augroup("remember_folds", { clear = true })
vim.api.nvim_create_autocmd("BufWinLeave", {
	group = "remember_folds",
	pattern = "?*",
	command = "mkview 1",
})
vim.api.nvim_create_autocmd("BufWinEnter", {
	group = "remember_folds",
	pattern = "?*",
	command = "silent! loadview 1",
})

-- enable autocompletion for LSP
vim.api.nvim_create_autocmd("LspAttach", {
	callback = function(ev)
		local client = vim.lsp.get_client_by_id(ev.data.client_id)
		if client:supports_method("textDocument/completion") then
			vim.lsp.completion.enable(true, client.id, ev.buf, {
				autotrigger = true,
				convert = function(item)
					return { abbr = item.label:gsub("%b()", "") }
				end,
			})
		end
	end,
})

-- vim dadbod config
vim.g.db_ui_use_omni = 1
vim.g.db_ui_connections_json = vim.fn.expand("~/.local/share/db_ui/connections.json")
vim.g.db_completion_enabled = 1
vim.g.omni_sql_no_default_maps = 1
vim.api.nvim_create_autocmd("FileType", {
	pattern = { "sql", "mysql", "plsql" },
	callback = function()
		vim.bo.omnifunc = "vim_dadbod_completion#omni"
		vim.bo.completefunc = "vim_dadbod_completion#omni"
		vim.bo.commentstring = "-- %s"
	end,
})
vim.api.nvim_create_autocmd("FileType", {
	pattern = "dbui",
	callback = function()
		vim.bo.buflisted = false
	end,
})

-- Set up compilers for langs that neovim doesnt support by default
local compiler_configs = {
	typescript = {
		patterns = { "typescript", "typescriptreact" },
		makeprg = "sh -c 'yarn run tsc -b --noEmit --pretty false ; yarn eslint --quiet --format unix .'",
		errorformat = {
			-- tsc
			"%f(%l\\,%c): error TS%n: %m",
			"%f(%l\\,%c): warning TS%n: %m",

			-- eslint (unix)
			"%f:%l:%c: %m",

			-- ignore yarn / eslint noise
			"%-Gerror Command failed%.%#",
			"%-Ginfo Visit%.%#",
			"%-Gyarn run v%.%#",
			"%-G%\\d%\\+ problem%.%#",
			"%-G$%.%#",
		},
	},
}

for _, config in pairs(compiler_configs) do
	vim.api.nvim_create_autocmd("FileType", {
		pattern = config.patterns,
		callback = function()
			vim.opt_local.makeprg = config.makeprg
			vim.opt_local.errorformat = config.errorformat
		end,
		desc = "Set up compiler for " .. table.concat(config.patterns, ", "),
	})
end

vim.api.nvim_create_autocmd("QuickFixCmdPost", {
	pattern = "make",
	callback = function()
		local qf = vim.fn.getqflist()
		for _, item in ipairs(qf) do
			if item.valid == 1 then
				vim.cmd("copen")
				return
			end
		end
	end,
})

-- this is just so if im in os repos, the indent is 2 spaces (on personal laptop)
local function set_os_project_indent()
	local file = vim.fn.expand("%:p")
	local home = vim.fn.expand("~")

	-- match ~/projects/os*
	if file:match("^" .. home .. "/projects/os[^/]+/") then
		vim.opt_local.tabstop = 2
		vim.opt_local.softtabstop = 2
		vim.opt_local.shiftwidth = 2
		vim.opt_local.expandtab = true
	end
end

vim.api.nvim_create_autocmd({ "BufRead", "BufNewFile" }, {
	callback = set_os_project_indent,
})
