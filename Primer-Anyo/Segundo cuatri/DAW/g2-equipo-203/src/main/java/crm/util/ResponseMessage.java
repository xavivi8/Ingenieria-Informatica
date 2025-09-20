package crm.util;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class ResponseMessage {
    private String message;

    // Constructor
    public ResponseMessage(String message) {
        this.message = message;
    }
}
