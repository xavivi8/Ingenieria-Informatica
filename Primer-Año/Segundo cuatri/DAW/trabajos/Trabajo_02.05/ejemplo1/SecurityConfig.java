package daw.app.seguridad;

import daw.app.bean.Usuario;
import daw.app.dao.UsuarioDAO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.dao.DaoAuthenticationProvider;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.NoOpPasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;

import java.util.Collections;


@Configuration
@EnableWebSecurity
public class SecurityConfig {

    @Autowired
    UsuarioDAO usuarioDAO;

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
            http
                .formLogin(form -> form
                        .loginPage("/login.jsp")
                        .loginProcessingUrl("/loginUser")
                        .failureUrl("/login.jsp?error=true")
                        .defaultSuccessUrl("/eventos/listadoEventos", true)
                        .permitAll()
                )
                .authorizeHttpRequests((auth) -> auth
                    .requestMatchers(
                            "/login.jsp",
                            "/usuarios/form",
                            "/WEB-INF/jsp/usuarios/CrearUsuario.jsp"
                    ).permitAll()
                    .requestMatchers(
                            "/eventos/form",
                            "/WEB-INF/jsp/eventos/CrearEvento.jsp",
                            "/eventos/modificaEvento",
                            "/WEB-INF/jsp/eventos/ModificarEvento.jsp",
                            "/eventos/borra").hasRole("ADMIN")
                    .anyRequest().authenticated()
                )
                .logout(logout -> logout
                        .logoutUrl("/logout")
                        .logoutSuccessUrl("/login.jsp")
                        .permitAll()
                )
                .csrf(csrf -> csrf.disable());
        return http.build();
    }

    @Bean
    public UserDetailsService userDetailsService() {
        return username -> {
            Usuario usuario = usuarioDAO.buscaUsuario(username);
            if (usuario == null) {
                throw new UsernameNotFoundException("Usuario no encontrado");
            }

            if (usuario.getEmail().contains("@sportevents.es")) {
                return new User(
                        usuario.getEmail(),
                        "{noop}" + usuario.getContrasena(),
                        Collections.singletonList(new SimpleGrantedAuthority("ROLE_ADMIN"))
                );
            } else {
                return new User(
                        usuario.getEmail(),
                        "{noop}" + usuario.getContrasena(),
                        Collections.singletonList(new SimpleGrantedAuthority("ROLE_USER"))
                );
            }

        };
    }

}
