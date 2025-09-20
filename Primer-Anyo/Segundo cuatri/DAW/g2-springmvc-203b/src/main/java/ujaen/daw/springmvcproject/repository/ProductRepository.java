package ujaen.daw.springmvcproject.repository;

import org.springframework.data.repository.CrudRepository;
import ujaen.daw.springmvcproject.models.Product;

public interface ProductRepository extends CrudRepository<Product, Long> {
}
