/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package components;

import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.BasicFileAttributes;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.scene.control.TreeItem;

/**
 *
 *
 */
public class LoaderTreeItem extends TreeItem<String>{

   private String path;
   
   private boolean isDirectory;
   
   public LoaderTreeItem(Path file) {
       super(file.toString());
       this.path = file.toString();
       if (Files.isDirectory(file)) {
           this.isDirectory = true;
       } else {
           this.isDirectory = false;
       }
       
       if(!path.endsWith(File.separator)){
           String value = file.toString();
           int i = value.lastIndexOf(File.separator);
           if (i > 0) {
               this.setValue(value.substring(i+1));
           } else {
               this.setValue(value);
           }
       }
       
       this.addEventHandler(TreeItem.branchExpandedEvent(), new EventHandler(){
           @Override
           public void handle(Event e){
              LoaderTreeItem src = (LoaderTreeItem)e.getSource();
              if(src.isDirectory()&&src.isExpanded()) {
                  
              }
              try {
                  if (src.getChildren().isEmpty()) {
                      Path p = Paths.get(src.getPath());
                      BasicFileAttributes attr = Files.readAttributes(p, BasicFileAttributes.class);
                      if (attr.isDirectory()) {
                          DirectoryStream<Path> dir = Files.newDirectoryStream(p);
                          for (Path file:dir) {
                              LoaderTreeItem node = new LoaderTreeItem(file);
                              src.getChildren().add(node);
                          }
                      }
                  }
              } catch(IOException f) {
                  
              }
           }
       });
       this.addEventHandler(TreeItem.branchCollapsedEvent(), new EventHandler(){
           @Override
           public void handle(Event e) {
               LoaderTreeItem src = (LoaderTreeItem)e.getSource();
               if (src.isDirectory()&&!src.isExpanded()) {
                   
               }
           }
       });
   }
   
   public String getPath() {
       return this.path;
   }
   
   public boolean isDirectory() {
       return this.isDirectory;
   }
}
