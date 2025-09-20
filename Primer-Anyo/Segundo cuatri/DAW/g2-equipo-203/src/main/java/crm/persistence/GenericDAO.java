package crm.persistence;

import java.util.List;

public interface GenericDAO<T,K> {

    // CRUD
    public T create(T o);
    public T readById(K id);
    public T update(T o);
    public boolean delete(K id);

    public List<T> readAll();
    public boolean save(T o);
}

