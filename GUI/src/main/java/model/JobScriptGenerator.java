/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ardkastrati
 */
public class JobScriptGenerator {
   
    
    public static final String moabCommands = "        #### MOAB commands";
    public static final String directoryCommand = "        ##### Directory";
    public static final String shellCommands = "        #### MPI commands";
    public static final String msubPrefix = "#MSUB ";

    
    public ArrayList<String> createScript(JobScript script) {
        //TODO: pathname
        //File file = new File("src/main/resources/generated_docs/" + name + ".sh");
        ArrayList<String> lines = new ArrayList<>();
        lines.add(moabCommands);
        
        lines.add("");
        
        
        ArrayList<String> msubCommand = script.getMsubCommand().getScriptCommands();
        
        for(String line : msubCommand) {
            lines.add(msubPrefix + line);
        }
        lines.add("");
        lines.add("");
        lines.add(directoryCommand);
        lines.add("");
        lines.add(script.getDirectory());
        lines.add("");
        lines.add("");
        lines.add(shellCommands);
        lines.add("");
        lines.add(script.getMpirunCommand().getCommand());
        
        /* writer.write(moabCommands);
                writer.newLine();
                
                ArrayList<String> msubCommand = script.getMsubCommand().getScriptCommands();
                for(String line : msubCommand) {
                    writer.write(msubPrefix);
                    writer.write(line);
                    writer.newLine();
                }
                writer.write(directoryCommand);
                writer.newLine();
                writer.write(script.getDirectory());
                writer.newLine();
                writer.write(shellCommands);
                writer.newLine();
                
                writer.write(script.getMpirunCommand().toString());
                writer.close(); 
        } catch (IOException ex) {
            Logger.getLogger(JobScriptGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
        */
        
        
        return lines;
    }
    
    
}
