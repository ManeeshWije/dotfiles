return {
    "stevearc/conform.nvim",
    opts = {
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
    },
}
