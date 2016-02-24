/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.Compile;

import com.jcraft.jsch.Channel;
import model.commands.ICommand;
import java.util.ArrayList;

/**
 *
 * @author ardkastrati
 */
public enum Module implements ICommand{
    
    LOAD("load") {

        @Override
        public String toString() {
           return "module load";
        }
        
        
        
    },
    UNLOAD("unload") {

        @Override
        public String toString() {
           return "module unload";
        }
        
    },
    AVAIL("avail") {

        @Override
        public String toString() {
           return "module avail";
        }
        
    },
    LIST("list") {

        @Override
        public String toString() {
            return "module list";
        }
        
    };
    
    
    private String command;
    
    private Module(String command) {
        this.command = command;
    }

    @Override
    public String getCommand() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public ArrayList<String> getScriptCommands() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    /**
     *
     * @param command
     * @return
     */
    @Override
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }
    
    
    
}
