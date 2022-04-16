import Alpine from 'alpinejs';
import intersect from '@alpinejs/intersect';

import { render as renderPlain, setPause as setPausePlain } from '../src/plain/index.js';
import renderTriangle from '../src/triangle/index.js';
import { render as renderUniforms, pause as pauseUniforms, unpause as unpauseUniforms } from '../src/uniforms/index.js';
import { render as renderShaders, pause as pauseShaders, unpause as unpauseShaders } from '../src/shaders/index.js';

window.Alpine = Alpine; 

const onWebGlContextPlainColorLost = function () { alert('WebGL plain color context lost. You will need to reload the page.');   }
const onWebGlContextTriangleLost   = function () { alert('WebGL triangle color context lost. You will need to reload the page'); }
const onWebGlContextUniformsLost   = function () { alert('WebGL uniforms context lost. You will need to reload the page');       }
const onWebGlContextShadersLost    = function () { alert('WebGL shaders context lost. You will need to reload the page');        }

Alpine.plugin(intersect);

Alpine.data('main', () => ({
    renderers: [
        { 
            id: 'plain', 
            title: 'Hello Window',
            reference: 'https://learnopengl.com/Getting-started/Hello-Window',
            renderer: renderPlain, 
            onContextLost: onWebGlContextPlainColorLost,
            
            isPaused: true,

            onEnter: function () {
                setPausePlain(false);
            },

            onLeave: function () {
                if (!this.isPaused) {
                    setPausePlain(true);
                }
            },

            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);
            },
        }, 
        { 
            id: 'triangle', 
            title: 'Hello Triangle',
            reference: 'https://learnopengl.com/Getting-started/Hello-Triangle',
            renderer: renderTriangle,
            onContextLost: onWebGlContextTriangleLost,  

            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);
            },
        }, 
        { 
            id: 'uniforms', 
            title: 'Uniforms',
            reference: 'https://learnopengl.com/Getting-started/Shaders', 
            renderer: renderUniforms, 
            onContextLost: onWebGlContextUniformsLost,
            
            isPaused: true,

            onEnter: function () {
                unpauseUniforms();
            },

            onLeave: function () {
                if (!this.isPaused) {
                    pauseUniforms();
                }
            },

            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);
            },
        }, 
        { 
            id: 'shaders', 
            title: 'Shaders',
            reference: 'https://learnopengl.com/Getting-started/Shaders', 
            renderer: renderShaders, 
            onContextLost: onWebGlContextShadersLost,
            
            isPaused: true,

            onEnter: function () {
                unpauseShaders();
            },

            onLeave: function () {
                if (!this.isPaused) {
                    pauseShaders();
                }
            },

            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);
            },
        }, 
    ],
}));

Alpine.start();