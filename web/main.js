import Alpine from 'alpinejs';
import intersect from '@alpinejs/intersect';
import Toast from './ui/toast/toast.js';

import { render as renderPlain, setPause as setPausePlain } from '../src/plain/index.js';
import renderTriangle from '../src/triangle/index.js';
import { render as renderUniforms, pause as pauseUniforms, unpause as unpauseUniforms } from '../src/uniforms/index.js';
import { render as renderShaders, pause as pauseShaders, unpause as unpauseShaders } from '../src/shaders/index.js';

window.Alpine = Alpine; 
window.Toast = Toast;

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

            setPause: function (isPaused) {
                this.isPaused = isPaused;
                setPausePlain(isPaused);
            },

            onEnter: function () {
                this.isPaused = false;
                setPausePlain(false);
            },

            onLeave: function () {
                if (!this.isPaused) {
                    this.isPaused = true;
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

            setPause: function (isPaused) {
                this.isPaused = isPaused;
                if (isPaused) pauseUniforms();
                else unpauseUniforms();
            },

            onEnter: function () {
                this.isPaused = false;
                unpauseUniforms();
            },

            onLeave: function () {
                if (!this.isPaused) {
                    this.isPaused = true;
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

            setPause: function (isPaused) {
                this.isPaused = isPaused;
                if (isPaused) pauseShaders();
                else unpauseShaders();
            },

            onEnter: function () {
                this.isPaused = false;
                unpauseShaders();
            },

            onLeave: function () {
                if (!this.isPaused) {
                    this.isPaused = true;
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