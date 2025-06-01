package crm.persistence.map;

import crm.models.Product;
import crm.persistence.IProductDAO;
import crm.qualifiers.DAOMap;
import jakarta.enterprise.context.ApplicationScoped;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@ApplicationScoped
@DAOMap
public class ProductDAOMap implements IProductDAO, Serializable {
    private final Map<Long, Product> products;
    private Long currentId = 1L;

    public ProductDAOMap() {
        products = new HashMap<>();
    }

    @Override
    public void createProduct(Product product) {
        Product newProduct = new Product(product);
        newProduct.setId(currentId);
        this.products.put(currentId, newProduct);
        product.setId(currentId);
        currentId++;
    }

    @Override
    public Product getProductById(Long id) {
        Product product = products.get(id);
        return product != null ? new Product(product) : null;
    }

    @Override
    public List<Product> getAllProducts() {
        return this.products.values().stream().map(Product::new).collect(Collectors.toList());
    }

    @Override
    public void updateProduct(Product product) {
        if(this.products.containsKey(product.getId())) {
            Product updated = new Product(product);
            this.products.replace(product.getId(), updated);
        }
    }

    @Override
    public void deleteProduct(Long id) {
        this.products.remove(id);
    }
}
