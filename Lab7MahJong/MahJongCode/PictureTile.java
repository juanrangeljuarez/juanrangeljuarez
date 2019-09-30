
import java.awt.*;

import javax.imageio.ImageIO;
//import javax.print.DocFlavor.URL;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import	java.net.*;



abstract public class PictureTile extends Tile
{
	private String name;	
	private ImageIcon image;
	//protected static URL url;
	public PictureTile(String name)
	{
		setToolTipText(name);
		this.name = name;	
		name = "images/" + name + ".png";
		/*-image = new ImageIcon(name);
		image = new ImageIcon(image.getImage().				// Resize ImageIcon
					getScaledInstance((int)(image.getIconWidth()*0.8), -1, Image.SCALE_SMOOTH));*/
		//image = new ImageIcon(getClass().getResource(name));
		
		
		
		URL    url = PictureTile.class.getResource(name);
        image = new ImageIcon(url);
        image = new ImageIcon(image.getImage().				// Resize ImageIcon
				getScaledInstance((int)(image.getIconWidth()*0.8), -1, Image.SCALE_SMOOTH));
	/*	java.net.URL imgURL = getClass().getResource(name);
		image = new ImageIcon(imgURL);*/
        
        

		
		

		setVisible(true);
		
	}
	public String toString()
	{
		return name;
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawImage(image.getImage(), 12, 2, this);
	}
}