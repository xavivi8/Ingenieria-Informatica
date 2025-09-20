package ujaen.daw.springmvcproject.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ujaen.daw.springmvcproject.dto.ProductDTO;
import ujaen.daw.springmvcproject.models.Product;
import ujaen.daw.springmvcproject.persistence.IProductDAO;
import ujaen.daw.springmvcproject.service.IProductService;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class ProductServiceImpl implements IProductService {

    @Autowired
    private IProductDAO productDAO;

    @Override
    public List<ProductDTO> findAll() {
        List<Product> products = productDAO.findAll();

        // Mapeamos cada Product a ProductDTO usando un stream
        List<ProductDTO> productDTOs = products.stream().map(product -> {
            return new ProductDTO(
                    product.getId(),
                    product.getDescription(),
                    product.getName(),
                    product.getBase_price(),
                    product.getStock()
            );
        }).collect(Collectors.toList());

        return productDTOs;
    }

    @Override
    public ProductDTO findById(Long id) {
        Optional<Product> optionalProduct = productDAO.findById(id);

        return optionalProduct.map(product -> new ProductDTO(
                product.getId(),
                product.getDescription(),
                product.getName(),
                product.getBase_price(),
                product.getStock()
        )).orElse(null);
    }

    @Override
    public Product save(Product product) {
        return productDAO.save(product);
    }

    @Override
    public void deleteById(Long id) {
        productDAO.deleteById(id);
    }
}
