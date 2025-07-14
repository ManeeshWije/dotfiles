return {
    "saghen/blink.cmp",
    dependencies = {
        "L3MON4D3/LuaSnip",
        version = "v2.*",
        dependencies = {
            "rafamadriz/friendly-snippets",
            config = function()
                require("luasnip.loaders.from_vscode").lazy_load()
            end,
        },
    },
    version = "*",
    opts = {
        completion = {
            menu = {
                border = "single",
                winhighlight =
                    "Normal:BlinkCmpDoc,FloatBorder:BlinkCmpDocBorder,CursorLine:BlinkCmpMenuSelection,Search:None",
            },
            documentation = {
                window = {
                    border = "single",
                },
                auto_show = true,
                auto_show_delay_ms = 50,
            },
        },
        signature = {
            window = {
                border = "single",
            },
            enabled = true,
        },
        keymap = {
            preset = "default",
            ["<c-k>"] = { "scroll_documentation_up", "fallback" },
            ["<c-j>"] = { "scroll_documentation_down", "fallback" },
        },
        cmdline = {
            enabled = false
        },
        sources = {
            default = { "lsp", "path", "snippets", "buffer", "dadbod" },
            providers = {
                dadbod = {
                    name = "dadbod",
                    module = "vim_dadbod_completion.blink",
                    score_offset = 85,
                },
            },
        },
    },
}
