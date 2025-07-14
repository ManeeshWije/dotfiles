return {
    "ibhagwan/fzf-lua",
    dependencies = { "nvim-tree/nvim-web-devicons" },
    opts = {
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
    }
}
