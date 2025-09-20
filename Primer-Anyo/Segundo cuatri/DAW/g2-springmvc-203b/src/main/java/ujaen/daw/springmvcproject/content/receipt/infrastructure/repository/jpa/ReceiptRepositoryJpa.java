package ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa;

import org.springframework.data.jpa.repository.JpaRepository;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa.entity.ReceiptJpa;

public interface ReceiptRepositoryJpa extends JpaRepository<ReceiptJpa, Integer> {}