import { createRouter, createWebHistory } from 'vue-router'
import App from '@/App.vue'
import ProductHome from '@/views/product/ProductHome.vue'
import ProductCreate from '@/views/product/ProductCreate.vue'
import ProductEdit from '@/views/product/ProductEdit.vue'
import PayslipHome from '@/views/payslip/PayslipHome.vue'
import PayslipCreate from '@/views/payslip/PayslipCreate.vue'
import PayslipEdit from '@/views/payslip/PayslipEdit.vue'
import ReceiptHome from '@/views/receipt/ReceiptHome.vue'

const routes = [
  { path: '', name: 'ProductHome', component: ProductHome },
  { path: '/product', name: 'ProductHome', component: ProductHome },
  { path: '/product/create', name: 'ProductCreate', component: ProductCreate },
  {
    path: '/product/:id/edit',
    name: 'product-edit',
    component: ProductEdit,
    props: true
  },
  { path: '/payslip', name: 'PayslipHome', component: PayslipHome },
  { path: '/payslip/create', name: 'PayslipCreate', component: PayslipCreate },
  { path: '/receipt', name: 'Receipt', component: ReceiptHome },
   {
    path: '/payslip/:id/edit',
    name: 'payslip-edit',
    component: PayslipEdit,
    props: true
  },
]

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes
})

export default router