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
vim.opt.splitright = true
vim.opt.splitbelow = true
vim.opt.undofile = true
vim.opt.undodir = os.getenv("HOME") .. "/.vim/undo"
vim.opt.undolevels = 1000
vim.opt.undoreload = 10000
vim.o.autoread = true
vim.g.tsc_makeprg = "yarn run tsc"

-- Plugins
vim.pack.add({
	{ src = "https://github.com/nvim-lua/plenary.nvim" },
	{ src = "https://github.com/RRethy/base16-nvim" },
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter", version = "main" },
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter-context" },
	{ src = "https://github.com/ibhagwan/fzf-lua" },
	{ src = "https://github.com/iamcco/markdown-preview.nvim" },
	{ src = "https://github.com/stevearc/conform.nvim" },
	{ src = "https://github.com/tpope/vim-dadbod" },
	{ src = "https://github.com/kristijanhusak/vim-dadbod-ui" },
	{ src = "https://github.com/kristijanhusak/vim-dadbod-completion" },
	{ src = "https://github.com/neovim/nvim-lspconfig" },
	{ src = "https://github.com/christoomey/vim-tmux-navigator" },
	{ src = "https://github.com/github/copilot.vim" },
	{ src = "https://github.com/f-person/auto-dark-mode.nvim" },
	{ src = "https://github.com/ManeeshWije/git_browse.nvim" },
	{ src = "https://github.com/kdheepak/lazygit.nvim" },
	{ src = "https://github.com/crnvl96/lazydocker.nvim" },
	{ src = "https://github.com/mikavilpas/yazi.nvim" },
	{ src = "https://github.com/mason-org/mason.nvim" },
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

require("mason").setup()

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

local ensure_installed = {
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
}

local tree = require("nvim-treesitter")
tree.setup({})
tree.install(ensure_installed)

local grp = vim.api.nvim_create_augroup("TreeSitterConfig", { clear = true })
vim.api.nvim_create_autocmd("FileType", {
	group = grp,
	callback = function(event)
		if vim.list_contains(tree.get_installed(), vim.treesitter.language.get_lang(event.match)) then
			vim.treesitter.start(event.buf)
		end
	end,
})

require("treesitter-context").setup({
	enable = true,
})

require("conform").setup({
	notify_on_error = true,
	formatters_by_ft = {
		lua = { "stylua" },
		python = { "isort", "black" },
		java = { "google-java-format" },
		go = { "gofmt", "goimports" },
		rust = { "rustfmt" },
		php = { "php-cs-fixer" },
		c = { "clang-format" },
		sql = { "sql_formatter" },
		typescript = { "oxfmt" },
		typescriptreact = { "oxfmt" },
		javascript = { "oxfmt" },
		javascriptreact = { "oxfmt" },
		nix = { "nixfmt" },
		markdown = { "oxfmt" },
	},
	formatters = {
		sql_formatter = {
			command = "sql-formatter",
			args = { "--language", "postgresql" },
		},
	},
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

require("lazydocker").setup({
	window = {
		settings = {
			width = 0.9,
			height = 0.9,
			border = "single",
			relative = "editor",
		},
	},
})

vim.lsp.enable({
	"gopls",
	"lua_ls",
	"pyright",
	"clangd",
	"html",
	"cssls",
	"jsonls",
	"bashls",
	"dockerls",
	"yamlls",
	"rust_analyzer",
	"tailwindcss",
	"jdtls",
	"emmet_ls",
	"nil_ls",
})

-- Keymaps
-- fzf
local fzf = require("fzf-lua")
vim.keymap.set("n", "<leader>ff", fzf.files, { noremap = true, silent = true }) -- File find
vim.keymap.set("n", "<leader>fg", fzf.git_files, { noremap = true, silent = true }) -- Git file find
vim.keymap.set("n", "<leader>fb", fzf.buffers, { noremap = true, silent = true }) -- Find buffer
vim.keymap.set("n", "<leader>sg", fzf.grep_project, { noremap = true, silent = true }) -- Grep string
vim.keymap.set("n", "<leader>sm", fzf.spellcheck, { noremap = true, silent = true }) -- Misspelled words
vim.keymap.set("n", "<leader>sp", fzf.spell_suggest, { noremap = true, silent = true }) -- Suggestions for word under cursor
vim.keymap.set("n", "<leader>fh", fzf.help_tags, { noremap = true, silent = true }) -- Help tags
vim.keymap.set("n", "<leader>df", fzf.diagnostics_document, { noremap = true, silent = true }) -- Document Diagnostics

-- terminal apps
vim.keymap.set("n", "<leader>lz", "<cmd>LazyGit<CR>", { noremap = true, silent = true })
vim.keymap.set(
	{ "n", "t" },
	"<leader>ld",
	"<Cmd>lua require('lazydocker').toggle({ engine = 'docker' })<CR>",
	{ desc = "LazyDocker (docker)" }
)
vim.keymap.set("n", "<leader>e", function()
	require("yazi").yazi()
end)

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
end)
-- Terminal window navigation
vim.keymap.set("t", "<C-h>", [[<C-\><C-n><C-w>h]], { silent = true })
vim.keymap.set("t", "<C-j>", [[<C-\><C-n><C-w>j]], { silent = true })
vim.keymap.set("t", "<C-k>", [[<C-\><C-n><C-w>k]], { silent = true })
vim.keymap.set("t", "<C-l>", [[<C-\><C-n><C-w>l]], { silent = true })
vim.keymap.set("t", "<Esc><Esc>", [[<C-\><C-n>]], { desc = "Terminal normal mode" })
vim.keymap.set("n", "<leader>t", ":term<CR>", { desc = "Open terminal as new buffer" })
vim.keymap.set("n", "<leader>tv", ":botright vsplit | term<CR>", { desc = "Open terminal vertically" })
vim.keymap.set("n", "<leader>th", ":botright split | term<CR>", { desc = "Open terminal horizontally" })

-- Re-enter insert mode when focusing a terminal
vim.api.nvim_create_autocmd("WinEnter", {
	callback = function()
		if vim.bo.buftype == "terminal" then
			vim.cmd.startinsert()
		end
	end,
})

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

local projects = {
	"osbackendapi",
	"frontend",
	"backend",
}

if vim.list_contains(projects, vim.fn.fnamemodify(vim.fn.getcwd(), ":t")) then
	vim.lsp.enable("tsgo")
else
	vim.lsp.enable("ts_ls")

	require("conform").setup({
		notify_on_error = true,
		formatters_by_ft = {
			javascript = { "prettier" },
			typescript = { "prettier" },
			javascriptreact = { "prettier" },
			typescriptreact = { "prettier" },
			html = { "prettier" },
		},
	})
end

local compiler_configs = {
	typescript = {
		patterns = { "typescript", "typescriptreact" },
		compiler = "tsc",
	},
	rust = {
		patterns = { "rust" },
		compiler = "cargo",
	},
}

for _, config in pairs(compiler_configs) do
	vim.api.nvim_create_autocmd("FileType", {
		pattern = config.patterns,
		callback = function()
			vim.cmd("compiler " .. config.compiler)
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

local function set_os_project_indent()
	local file = vim.fn.expand("%:p")
	local workspace = vim.fn.expand("~/workspace")

	if file:match("^" .. workspace .. "/") then
		vim.opt_local.tabstop = 2
		vim.opt_local.softtabstop = 2
		vim.opt_local.shiftwidth = 2
		vim.opt_local.expandtab = true
	end
end

vim.api.nvim_create_autocmd({ "BufRead", "BufNewFile" }, {
	callback = set_os_project_indent,
})
