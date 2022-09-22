local vim = vim
vim.g.mapleader = ','
local execute = vim.api.nvim_command
local fn = vim.fn
-- ensure that packer is installed
local install_path = fn.stdpath('data') .. '/site/pack/packer/opt/packer.nvim'
if fn.empty(fn.glob(install_path)) > 0 then
  execute('!git clone https://github.com/wbthomason/packer.nvim ' .. install_path)
  execute 'packadd packer.nvim'
end
vim.cmd('packadd packer.nvim')
local packer = require 'packer'
local util = require 'packer.util'
packer.init({
  package_root = util.join_paths(vim.fn.stdpath('data'), 'site', 'pack')
})

local use = require('packer').use
require('packer').startup(function()
  use 'github/copilot.vim' -- bruh
  use 'lewis6991/gitsigns.nvim' -- git sign column
  use 'windwp/nvim-autopairs' -- auto brackets
  use 'neovim/nvim-lspconfig' -- lsp
  use { 'nvim-treesitter/nvim-treesitter', commit = '8ada8faf2fd5a74cc73090ec856fa88f34cd364b' } -- syntax highlighting
  use 'hrsh7th/cmp-nvim-lsp' -- lsp source for cmp
  use 'hrsh7th/nvim-cmp' -- auto-complete
  use 'SirVer/ultisnips' -- snippet source
  use 'quangnguyen30192/cmp-nvim-ultisnips' -- completion source
  use { 'prettier/vim-prettier', run = 'npm install' } -- prettier
  use 'nvim-lualine/lualine.nvim' -- status line
  use 'kyazdani42/nvim-web-devicons' -- icons
  use 'kyazdani42/nvim-tree.lua' -- file tree
  use 'preservim/nerdcommenter' -- better comments
  use 'ap/vim-css-color' -- css colours
  use 'nvim-lua/plenary.nvim' -- dependency for telescope
  use 'nvim-telescope/telescope.nvim' -- fuzzy find
  use 'arcticicestudio/nord-vim' -- colorscheme
  use 'epilande/vim-react-snippets' -- react snippets
  use 'nvim-lua/popup.nvim' -- popup
  use { 'turbio/bracey.vim', run = 'npm install --prefix server' } -- live server
end)

require('nvim-treesitter.configs').setup({
  ensure_installed = all,
  highlight = {
    enable = true,
    additional_vim_regex_highlighting = true
  },
  indent = {
    enable = true
  }
})
require('lualine').setup({
  options = { theme = 'nord' }
})
require('gitsigns').setup({
  current_line_blame = true
})
require('nvim-tree').setup({
  update_focused_file = {
    enable = true,
    update_cwd = true,
  },
})
require('nvim-autopairs').setup()

-- Mappings.
-- Use an on_attach function to only map the following keys
-- after the language server attaches to the current buffer
local on_attach = function(client, bufnr)
  local function map(mode, lhs, rhs, opts)
    opts = vim.tbl_extend('force', { noremap = true, silent = true }, opts or {})
    vim.api.nvim_buf_set_keymap(bufnr, mode, lhs, rhs, opts)
  end

  map('n', '<leader>e', '<cmd>lua vim.diagnostic.open_float()<CR>')
  map('n', '[d', '<cmd>lua vim.diagnostic.goto_prev()<CR>')
  map('n', ']d', '<cmd>lua vim.diagnostic.goto_next()<CR>')
  map('n', '<leader>q', '<cmd>lua vim.diagnostic.setloclist()<CR>')

  -- See `:help vim.lsp.*` for documentation on any of the below functions
  map('n', 'gD', '<cmd>lua vim.lsp.buf.declaration()<CR>')
  map('n', 'gd', '<cmd>lua vim.lsp.buf.definition()<CR>')
  map('n', 'K', '<cmd>lua vim.lsp.buf.hover()<CR>')
  map('n', 'gi', '<cmd>lua vim.lsp.buf.implementation()<CR>')
  map('n', '<C-k>', '<cmd>lua vim.lsp.buf.signature_help()<CR>')
  map('n', '<leader>wa', '<cmd>lua vim.lsp.buf.add_workspace_folder()<CR>')
  map('n', '<leader>wr', '<cmd>lua vim.lsp.buf.remove_workspace_folder()<CR>')
  map('n', '<leader>wl', '<cmd>lua print(vim.inspect(vim.lsp.buf.list_workspace_folders()))<CR>')
  map('n', '<leader>D', '<cmd>lua vim.lsp.buf.type_definition()<CR>')
  map('n', '<leader>rn', '<cmd>lua vim.lsp.buf.rename()<CR>')
  map('n', '<leader>ca', '<cmd>lua vim.lsp.buf.code_action()<CR>')
  map('n', 'gr', '<cmd>lua vim.lsp.buf.references()<CR>')
  map('n', '<leader>f', '<cmd>lua vim.lsp.buf.formatting()<CR>')

  -- Navigation
  map('n', ']c', "&diff ? ']c' : '<cmd>Gitsigns next_hunk<CR>'", { expr = true })
  map('n', '[c', "&diff ? '[c' : '<cmd>Gitsigns prev_hunk<CR>'", { expr = true })

  -- Actions
  map('n', '<leader>hs', ':Gitsigns stage_hunk<CR>')
  map('v', '<leader>hs', ':Gitsigns stage_hunk<CR>')
  map('n', '<leader>hr', ':Gitsigns reset_hunk<CR>')
  map('v', '<leader>hr', ':Gitsigns reset_hunk<CR>')
  map('n', '<leader>hS', '<cmd>Gitsigns stage_buffer<CR>')
  map('n', '<leader>hu', '<cmd>Gitsigns undo_stage_hunk<CR>')
  map('n', '<leader>hR', '<cmd>Gitsigns reset_buffer<CR>')
  map('n', '<leader>hp', '<cmd>Gitsigns preview_hunk<CR>')
  map('n', '<leader>hb', '<cmd>lua require"gitsigns".blame_line{full=true}<CR>')
  map('n', '<leader>tb', '<cmd>Gitsigns toggle_current_line_blame<CR>')
  map('n', '<leader>hd', '<cmd>Gitsigns diffthis<CR>')
  map('n', '<leader>hD', '<cmd>lua require"gitsigns".diffthis("~")<CR>')
  map('n', '<leader>td', '<cmd>Gitsigns toggle_deleted<CR>')

  -- Text object
  map('o', 'ih', ':<C-U>Gitsigns select_hunk<CR>')
  map('x', 'ih', ':<C-U>Gitsigns select_hunk<CR>')
end

-- Setup nvim-cmp.
local cmp = require 'cmp'

cmp.setup({
  snippet = {
    -- REQUIRED - you must specify a snippet engine
    expand = function(args)
      vim.fn["UltiSnips#Anon"](args.body) -- For `ultisnips` users.
    end,
  },
  window = {
    completion = cmp.config.window.bordered(),
    documentation = cmp.config.window.bordered(),
  },
  mapping = cmp.mapping.preset.insert({
    ['<C-b>'] = cmp.mapping.scroll_docs(-4),
    ['<C-f>'] = cmp.mapping.scroll_docs(4),
    ['<C-Space>'] = cmp.mapping.complete(),
    ['<C-e>'] = cmp.mapping.abort(),
    ['<CR>'] = cmp.mapping.confirm({ select = true }), -- Accept currently selected item. Set `select` to `false` to only confirm explicitly selected items.
    ['<Tab>'] = cmp.mapping(function(fallback)
      if cmp.visible() then
        cmp.select_next_item()
      else
        fallback()
      end
    end, { 'i', 's' }),
    ['<S-Tab>'] = cmp.mapping(function(fallback)
      if cmp.visible() then
        cmp.select_prev_item()
      else
        fallback()
      end
    end, { 'i', 's' }),
  }),
  sources = cmp.config.sources({
    { name = 'nvim_lsp' },
    { name = 'ultisnips' }, -- For ultisnips users.
    { name = 'cmp_nvim_lsp' },
  }, {
    { name = 'buffer' },
  })
})

-- Setup lspconfig.
local capabilities = require('cmp_nvim_lsp').update_capabilities(vim.lsp.protocol.make_client_capabilities())
capabilities.textDocument.completion.completionItem.snippetSupport = true

-- setup language servers here
local lspconfig = require('lspconfig')
local servers = { 'jdtls', 'sumneko_lua', 'tsserver', 'eslint', 'emmet_ls', 'html', 'vimls', 'bashls', 'clangd', 'cssls',
  'gopls', 'graphql', 'rust_analyzer', 'dockerls', 'jsonls', 'ltex', 'pyright', 'sqlls', 'tailwindcss' }

for _, lsp in ipairs(servers) do
  lspconfig[lsp].setup {
    on_attach = on_attach,
    capabilities = capabilities,
  }
end

-- default options
local options = {
  backup = false, -- creates a backup file
  clipboard = 'unnamedplus', -- allows neovim to access the system clipboard
  cmdheight = 2, -- more space in the neovim command line for displaying messages
  completeopt = { 'menuone', 'noselect' }, -- mostly just for cmp
  fileencoding = 'utf-8', -- the encoding written to a file
  hlsearch = true, -- highlight all matches on previous search pattern
  mouse = 'a', -- allow the mouse to be used in neovim
  showmode = false, -- we don't need to see things like -- INSERT -- anymore
  wildmenu = true, -- show menu on the bottom
  smartcase = true, -- smart case
  smartindent = true, -- make indenting smarter again
  swapfile = false, -- disable swapfile
  termguicolors = true, -- set term gui colors (most terminals support this)
  undofile = true, -- enable persistent undo
  updatetime = 50, -- faster completion (4000ms default)
  writebackup = false, -- if a file is being edited by another program (or was written to file while editing with another program), it is not allowed to be edited
  expandtab = true, -- convert tabs to spaces
  shiftwidth = 2, -- the number of spaces inserted for each indentation
  tabstop = 2, -- insert 2 spaces for a tab
  number = true, -- set numbered lines
  relativenumber = true, -- set relative numbered lines
  signcolumn = 'yes', -- always show the sign column, otherwise it would shift the text each time
  wrap = false, -- display lines as one long line
  scrolloff = 8, -- scroll when 8 lines above or below
  syntax = 'on', -- syntax highlighting
  guicursor = '', -- cursor block in insert
  cursorline = true, -- highlight the current line
}

for k, v in pairs(options) do
  vim.opt[k] = v
end

vim.cmd([[
set whichwrap+=<,>,[,],h,l"
set iskeyword+=-

" Fix italics in Vim
if !has('nvim')
  let &t_ZH="\e[3m"
  let &t_ZR="\e[23m"
endif

" so useful
inoremap jk <ESC>

" For Neovim 0.1.3 and 0.1.4 - https://github.com/neovim/neovim/pull/2198
if (has('nvim'))
  let $NVIM_TUI_ENABLE_TRUE_COLOR = 1
endif

colorscheme nord
hi! Normal ctermbg=NONE guibg=NONE 
hi! NonText ctermbg=NONE guibg=NONE guifg=NONE ctermfg=NONE

" Nerd Commenter keybinds
" Create default mappings
let g:NERDCreateDefaultMappings = 1
" Add spaces after comment delimiters by default
let g:NERDSpaceDelims = 1
" Use compact syntax for prettified multi-line comments
let g:NERDCompactSexyComs = 1
" Align line-wise comment delimiters flush left instead of following code indentation
let g:NERDDefaultAlign = 'left'
" Set a language to use its alternate delimiters by default
let g:NERDAltDelims_java = 1
" Add your own custom formats or override the defaults
let g:NERDCustomDelimiters = { 'c': { 'left': '/**','right': '*/' } }
" Allow commenting and inverting empty lines (useful when commenting a region)
let g:NERDCommentEmptyLines = 1
" Enable trimming of trailing whitespace when uncommenting
let g:NERDTrimTrailingWhitespace = 1
" Enable NERDCommenterToggle to check all selected lines is commented or not 
let g:NERDToggleCheckAllLines = 1

" File tree keybinds
nnoremap <C-n> :NvimTreeToggle<CR>
nnoremap <leader>r :NvimTreeRefresh<CR>
nnoremap <leader>n :NvimTreeFindFile<CR>

" Telescope keybinds
nnoremap <leader>ff <cmd>lua require('telescope.builtin').find_files()<cr>
nnoremap <leader>fg <cmd>lua require('telescope.builtin').live_grep()<cr>
nnoremap <leader>fs <cmd>lua require('telescope.builtin').grep_string()<cr>
nnoremap <leader>fb <cmd>lua require('telescope.builtin').buffers()<cr>
nnoremap <leader>fh <cmd>lua require('telescope.builtin').help_tags()<cr>

" Correct spaces when writing python
let g:python_recommended_style = 0

" Prettier stuff
let g:prettier#autoformat = 1
let g:prettier#autoformat_config_present = 1
]])
