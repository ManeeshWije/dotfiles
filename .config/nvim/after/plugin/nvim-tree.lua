-- disable netrw at the very start of your init.lua (strongly advised)
vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1
require("nvim-tree").setup({
    sort_by = "case_sensitive",
    view = {
        width = 30,
        side = "right"
    },
    renderer = {
        group_empty = true,
    },
    filters = {
        dotfiles = false,
    },
    update_focused_file = {
        enable = true,
        update_root = true,
    },
})
