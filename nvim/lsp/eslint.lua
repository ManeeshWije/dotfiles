return {
    cmd = {
        "vscode-eslint-language-server",
        "--stdio",
    },
    filetypes = {
        "javascript",
        "javascriptreact",
        "javascript.jsx",
        "typescript",
        "typescriptreact",
        "typescript.tsx",
        "vue",
        "svelte",
        "astro",
        "htmlangular"
    },
    settings = {
        validate = 'on',
        packageManager = nil,
        useESLintClass = false,
        experimental = {
            useFlatConfig = false,
        },
        codeActionOnSave = {
            enable = false,
            mode = 'all',
        },
        format = true,
        quiet = false,
        onIgnoredFiles = 'off',
        rulesCustomizations = {},
        run = 'onType',
        problems = {
            shortenToSingleLine = false,
        },
        -- nodePath configures the directory in which the eslint server should start its node_modules resolution.
        -- This path is relative to the workspace folder (root dir) of the server instance.
        nodePath = '',
        -- use the workspace folder location or the file location (if no workspace folder is open) as the working directory
        workingDirectory = { mode = 'location' },
        codeAction = {
            disableRuleComment = {
                enable = true,
                location = 'separateLine',
            },
            showDocumentation = {
                enable = true,
            },
        },
    },
}
