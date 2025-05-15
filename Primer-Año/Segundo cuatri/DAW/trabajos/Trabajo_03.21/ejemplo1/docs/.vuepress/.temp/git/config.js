import { GitContributors } from "C:/Users/Usuario/Mi unidad (gcg00035@red.ujaen.es)/Uni/3 Grado/2 Cuatrimestre/DAW/trabajo_dirigido/node_modules/@vuepress/plugin-git/lib/client/components/GitContributors.js";
import { GitChangelog } from "C:/Users/Usuario/Mi unidad (gcg00035@red.ujaen.es)/Uni/3 Grado/2 Cuatrimestre/DAW/trabajo_dirigido/node_modules/@vuepress/plugin-git/lib/client/components/GitChangelog.js";

export default {
  enhance: ({ app }) => {
    app.component("GitContributors", GitContributors);
    app.component("GitChangelog", GitChangelog);
  },
};
