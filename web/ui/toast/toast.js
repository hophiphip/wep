import './toast.css';

const toastGroupClass = 'toast-group';
const toastClass      = 'toast';

/**
 * Initialize toast component.
 * @param {HTMLElement} element 
 * @returns 
 */
export const init = () => {
    const node = document.createElement('section');
    node.classList.add(toastGroupClass);

    document.firstElementChild.insertBefore(node, document.body);
    return node;
}

const createToast = text => {
    const node = document.createElement('output');

    node.innerText = text;
    node.classList.add(toastClass);
    node.setAttribute('role', 'status');
    node.setAttribute('aria-live', 'polite');

    return node;
}

const addToast = toast => {
    const { matches: motionOK } = window.matchMedia(
        '(prefers-reduced-motion: no-preference)'
    );

    ToastContainer.children.length && motionOK
        ? flipToast(toast)
        : ToastContainer.appendChild(toast);
}

export const Toast = text => {
    let toast = createToast(text);

    addToast(toast);

    return new Promise(async (resolve, reject) => {
        await Promise.allSettled(
            toast.getAnimations().map(animation =>
                animation.finished
            )
        );

        ToastContainer.removeChild(toast);
        resolve();
    })
}

const flipToast = toast => { // https://aerotwist.com/blog/flip-your-animations/
    const first = ToastContainer.offsetHeight;

    ToastContainer.appendChild(toast);

    const last = ToastContainer.offsetHeight;

    const invert = last - first;

    const animation = ToastContainer.animate([
        { transform: `translateY(${invert}px)` },
        { transform: 'translateY(0)' }
    ], {
        duration: 150,
        easing: 'ease-out',
    });

    animation.startTime = document.timeline.currentTime;
}

const ToastContainer = init();

export default Toast;