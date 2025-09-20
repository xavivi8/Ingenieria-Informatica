package ujaen.daw.springmvcproject.service;

import ujaen.daw.springmvcproject.dto.ProductDTO;
import ujaen.daw.springmvcproject.models.Product;

import java.util.List;

public interface IProductService {

    List<ProductDTO> findAll();

    ProductDTO findById(Long id);

    Product save(Product product);

    void deleteById(Long id);
}
