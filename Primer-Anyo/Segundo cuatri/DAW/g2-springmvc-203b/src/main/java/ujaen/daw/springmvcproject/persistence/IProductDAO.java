package ujaen.daw.springmvcproject.persistence;

import ujaen.daw.springmvcproject.models.Product;

import java.util.List;
import java.util.Optional;

public interface IProductDAO {

    List<Product> findAll();

    Optional<Product> findById(Long id);

    Product save(Product product);

    void deleteById(Long id);
}
