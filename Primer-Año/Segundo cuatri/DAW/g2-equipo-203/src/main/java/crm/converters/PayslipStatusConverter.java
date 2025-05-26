package crm.converters;

import crm.enums.PayslipStatus;
import jakarta.faces.component.UIComponent;
import jakarta.faces.context.FacesContext;
import jakarta.faces.convert.Converter;
import jakarta.faces.convert.FacesConverter;

@FacesConverter(value = "payslipStatusConverter")
public class PayslipStatusConverter implements Converter<PayslipStatus> {

    @Override
    public PayslipStatus getAsObject(FacesContext context, UIComponent component, String value) {
        if (value == null || value.isEmpty()) {
            return null;
        }
        return PayslipStatus.valueOf(value); // Convierte la cadena en el Enum
    }

    @Override
    public String getAsString(FacesContext context, UIComponent component, PayslipStatus value) {
        if (value == null) {
            return "";
        }
        return value.name(); // Devuelve el nombre del Enum como String
    }
}
