//Para ejecutar un preview lanzar desde la terminal: npx http-server docs/.vuepress/dist
import { defineUserConfig } from 'vuepress'
import { defaultTheme } from '@vuepress/theme-default'
import { viteBundler } from '@vuepress/bundler-vite'

export default defineUserConfig({
    lang: 'es-ES',
    title: 'Recetas de Cocina',
    description: 'Un recetario personal con VuePress',
    base: '/app/docs/',

    theme: defaultTheme({

        contributors: false,
        lastUpdated: false,
        navbar: [
            { text: 'Inicio', link: '/' },
            { text: 'Recetas', link: '/recetas/'},
            {text: 'BarTech', link: '../app/', target: '_blank', rel: 'external'}
        ],
        sidebar: false

    }),



    bundler: viteBundler()
})
