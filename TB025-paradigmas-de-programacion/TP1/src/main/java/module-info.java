module org.pdp {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;

    exports org.pdp.view;
    opens org.pdp.controller to javafx.fxml;
}