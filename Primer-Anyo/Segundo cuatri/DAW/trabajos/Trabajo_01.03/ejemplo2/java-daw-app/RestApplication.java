package daw.app;

import jakarta.ws.rs.ApplicationPath;
import jakarta.ws.rs.core.Application;

@ApplicationPath("/api")
public class RestApplication extends Application {
    // vacía: con esto JAX‑RS ya arranca en /api
}