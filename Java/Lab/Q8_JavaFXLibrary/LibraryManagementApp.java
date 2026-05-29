import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;

public class LibraryManagementApp extends Application {

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Library Management System");

        BorderPane mainPane = new BorderPane();

        // Menu Bar
        MenuBar menuBar = new MenuBar();
        Menu menuFile = new Menu("File");
        MenuItem itemOpen = new MenuItem("Open...");
        MenuItem itemExit = new MenuItem("Exit");
        menuFile.getItems().addAll(itemOpen, itemExit);
        menuBar.getMenus().add(menuFile);

        itemOpen.setOnAction(e -> {
            FileChooser fileChooser = new FileChooser();
            File file = fileChooser.showOpenDialog(primaryStage);
            if (file != null) {
                System.out.println("Selected file: " + file.getAbsolutePath());
            }
        });
        itemExit.setOnAction(e -> System.exit(0));

        // Form Pane
        GridPane gridPane = new GridPane();
        gridPane.setPadding(new Insets(10));
        gridPane.setHgap(10);
        gridPane.setVgap(10);

        gridPane.add(new Label("Book Title:"), 0, 0);
        TextField tfTitle = new TextField();
        gridPane.add(tfTitle, 1, 0);

        gridPane.add(new Label("Genre:"), 0, 1);
        HBox rdBox = new HBox(10);
        ToggleGroup group = new ToggleGroup();
        RadioButton rbFiction = new RadioButton("Fiction");
        rbFiction.setToggleGroup(group);
        RadioButton rbNonFiction = new RadioButton("Non-Fiction");
        rbNonFiction.setToggleGroup(group);
        rdBox.getChildren().addAll(rbFiction, rbNonFiction);
        gridPane.add(rdBox, 1, 1);

        CheckBox cbAvailable = new CheckBox("Available");
        gridPane.add(cbAvailable, 1, 2);

        Button btnAdd = new Button("Add Book");
        btnAdd.setTooltip(new Tooltip("Click to add book to the library"));
        gridPane.add(btnAdd, 1, 3);

        mainPane.setTop(menuBar);
        mainPane.setCenter(gridPane);

        Scene scene = new Scene(mainPane, 400, 300);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
