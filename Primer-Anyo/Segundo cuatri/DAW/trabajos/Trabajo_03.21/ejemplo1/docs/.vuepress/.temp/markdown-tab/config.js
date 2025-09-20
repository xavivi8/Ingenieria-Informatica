import { CodeTabs } from "C:/Users/Usuario/Mi unidad (gcg00035@red.ujaen.es)/Uni/3 Grado/2 Cuatrimestre/DAW/trabajo_dirigido/node_modules/@vuepress/plugin-markdown-tab/lib/client/components/CodeTabs.js";
import { Tabs } from "C:/Users/Usuario/Mi unidad (gcg00035@red.ujaen.es)/Uni/3 Grado/2 Cuatrimestre/DAW/trabajo_dirigido/node_modules/@vuepress/plugin-markdown-tab/lib/client/components/Tabs.js";
import "C:/Users/Usuario/Mi unidad (gcg00035@red.ujaen.es)/Uni/3 Grado/2 Cuatrimestre/DAW/trabajo_dirigido/node_modules/@vuepress/plugin-markdown-tab/lib/client/styles/vars.css";

export default {
  enhance: ({ app }) => {
    app.component("CodeTabs", CodeTabs);
    app.component("Tabs", Tabs);
  },
};
