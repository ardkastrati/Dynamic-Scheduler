/*
 * Here comes the text of your license
 * Each line should be prefixed with  * 
 */
package services;

import com.jcraft.jsch.Channel;
import com.jcraft.jsch.ChannelSftp;
import com.jcraft.jsch.Session;
import javafx.concurrent.Task;

/**
 *
 * @author ardkastrati
 */
public class CreateNewChannelTask extends Task<Channel> {

    private Session currentSession;
    private String channelType;
    
    public CreateNewChannelTask(Session session, String channelType) {
        this.currentSession = session; 
        this.channelType = channelType;
    }
    
    @Override
    protected Channel call() throws Exception {
        Channel channel = currentSession.openChannel(channelType);
        
        channel.connect();
        System.out.println("Channel opened");
        return channel;
    }
    
}
