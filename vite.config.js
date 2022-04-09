import { defineConfig } from 'vite'

const basePath = '/'

export default defineConfig({
    optimizeDeps: {
        esbuildOptions: {
            target: 'es2020', // https://github.com/vitejs/vite/issues/7364
        },
    },

    build: {
        rollupOptions: {
            output: {
                assetFileNames: `assets/[name].[ext]` // https://github.com/vitejs/vite/issues/378
            }
        },
        target: 'es2020', // https://github.com/vitejs/vite/issues/7364
    },

    base: basePath,
})
