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
    "sqlls",
    "eslint",
    "tailwindcss",
    "jdtls",
})

vim.diagnostic.config({
    -- virtual_lines = true,
    virtual_text = true,
    underline = true,
    update_in_insert = false,
    severity_sort = true,
    float = {
        border = "single",
        source = true,
    },
    signs = {
        text = {
            [vim.diagnostic.severity.ERROR] = "󰅚 ",
            [vim.diagnostic.severity.WARN] = "󰀪 ",
            [vim.diagnostic.severity.INFO] = "󰋽 ",
            [vim.diagnostic.severity.HINT] = "󰌶 ",
        },
        numhl = {
            [vim.diagnostic.severity.ERROR] = "ErrorMsg",
            [vim.diagnostic.severity.WARN] = "WarningMsg",
        },
    },
})
