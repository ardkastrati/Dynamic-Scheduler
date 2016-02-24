/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package model.commands.MPI;


import java.util.ArrayList;
import java.util.LinkedList;
import model.commands.ICommand;

/**
 *
 * @author ardkastrati
 */
public class MpiRun implements ICommand {

    public enum SchedulingDesign {
        MASTER_WORKER("master-worker"),
        MULTI_QUEUE("multi-queue");
        
        private final String name;
        private SchedulingDesign(String name) {
            this.name = name;
        }
        
        public String getName() {
           return this.name;
        }
        
        public static SchedulingDesign getDesignFromName(String name) {
            SchedulingDesign design = null;
            switch(name) {
                case "Master/Worker Design" :
                    design = SchedulingDesign.MASTER_WORKER;
                    break;
                case "Multi-Queue Design" :
                    design = SchedulingDesign.MULTI_QUEUE;
                    break;
                default :
                    assert false;
                    break;
            }
            return design;
        }
        
    }
    
    public enum SchedulingStrategy {
        FIFO("fifo"),
        LIFO("lifo"),
        SJF("sjf"),
        LJF("ljf");
        
        private final String name;
        private SchedulingStrategy(String name) {
            this.name = name;
        }
        
        public String getName() {
           return this.name;
        }
        
        public static SchedulingStrategy getDesignFromName(String name) {
            SchedulingStrategy strategy = null;
            switch(name) {
                case "FIFO" :
                    strategy = SchedulingStrategy.FIFO;
                    break;
                case "LIFO" :
                    strategy = SchedulingStrategy.LIFO;
                    break;
                case "SJF" :
                    strategy = SchedulingStrategy.SJF;
                    break;
                case "LJF" :
                    strategy = SchedulingStrategy.SJF;
                    break;
                default :
                    assert false;
                    break;
            }
            return strategy;
        }
    }
    
    private String parameter;
    private SchedulingDesign design;
    private SchedulingStrategy strategy;
    
    public void setParameter(String parameter) {
        this.parameter = parameter;
    }
    public void setDesign(SchedulingDesign design) {
        this.design = design;
    }
    
    public void setStrategy(SchedulingStrategy strategy) {
        this.strategy = strategy;
    }
           
    @Override
    public String getCommand() {
        StringBuilder command = new StringBuilder();
        command.append("mpirun ");
        command.append(parameter);
        if(design != null && strategy != null) {
            command.append(" -design ");
            command.append(design.getName());
            command.append(" -strategy ");
            command.append(strategy.getName());
        }
        
        return command.toString();
    }

    @Override
    public ArrayList<String> getScriptCommands() {
        ArrayList<String> scriptCommands = new ArrayList<>();
        scriptCommands.add(getCommand());
        return scriptCommands;
    }

    @Override
    public String toString() {
       return "mpirun";
    }
    
    /**
     *
     * @param command
     * @return
     */
    public boolean equals(ICommand command) {
       return command.toString().equalsIgnoreCase(this.toString());        
    }
    
}
