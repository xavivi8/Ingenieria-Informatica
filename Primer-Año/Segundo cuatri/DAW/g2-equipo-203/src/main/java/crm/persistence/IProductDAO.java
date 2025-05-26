package crm.persistence;

import crm.models.Product;

import java.util.List;

public interface IProductDAO {

    void createProduct(Product product);

    Product getProductById(Long id);

    List<Product> getAllProducts();

    void updateProduct(Product product);

    void deleteProduct(Long id);
}
