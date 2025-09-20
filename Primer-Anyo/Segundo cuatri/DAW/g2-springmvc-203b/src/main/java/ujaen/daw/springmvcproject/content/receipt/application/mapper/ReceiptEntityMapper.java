package ujaen.daw.springmvcproject.content.receipt.application.mapper;

import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.factory.Mappers;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.controller.dto.input.ReceiptInputDto;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.controller.dto.input.ReceiptUpdateInputDto;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa.entity.ReceiptJpa;

import java.util.List;

@Mapper(componentModel = "spring")
public interface ReceiptEntityMapper {

    ReceiptEntityMapper INSTANCE = Mappers.getMapper(ReceiptEntityMapper.class);


    // Entity
    @Mapping(target = "id", ignore = true)
    Receipt toEntity(ReceiptInputDto receiptInputDto);

    Receipt toEntity(ReceiptUpdateInputDto receiptUpdateInputDto);

    Receipt toEntity(ReceiptJpa receiptJpa);

    // Entity JPA
    @Mapping(target = "id", ignore = true)
    ReceiptJpa toEntityJpa(Receipt receipt);

    List<Receipt> toEntityList(List<ReceiptJpa> receiptJpaList);
}