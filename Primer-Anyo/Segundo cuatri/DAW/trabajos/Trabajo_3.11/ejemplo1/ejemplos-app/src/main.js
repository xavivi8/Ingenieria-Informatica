import { createApp } from 'vue';
import App from './App.vue';

import PrimeVue from 'primevue/config';
import Aura from '@primeuix/themes/aura';

import Button from 'primevue/button';
import Menubar from 'primevue/menubar';
import InputText from 'primevue/inputtext';
import Password from 'primevue/password';
import Card from 'primevue/card';
import { Form } from '@primevue/forms';
import Toast from 'primevue/toast';
import ToastService from 'primevue/toastservice';


const app = createApp(App);
app.use(PrimeVue, {
    theme: {
        preset: Aura,
        options: {
            prefix: 'p',
            darkModeSelector: 'system',
            cssLayer: false
        }
    }
});

app.use(ToastService);
app.use(Form)
app.component('Menubar', Menubar);
app.component('InputText', InputText);
app.component('Password', Password);
app.component('Card', Card);
app.component('Button', Button);
app.component('Toast', Toast);
app.mount('#app');