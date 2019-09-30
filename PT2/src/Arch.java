import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import java.net.*;
public class Arch extends JFrame
{
	private Image image;
	public Arch()
	{
		setTitle("Arch");
		setSize(490,390);
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		addWindowListener(new WindowAdapter() {public void windowClosing(WindowEvent e)
			{close();}
		});
		
		
	try 
		{
			URL url = new URL("https://www.nps.gov/arch/learn/photosmultimedia/upload/arches3.jpg");
			image = Toolkit.getDefaultToolkit().getImage(url);	
		}
		catch(MalformedURLException murle)
		{
			JOptionPane.showMessageDialog(this, "Bad URL: "+ murle, "Image Error", JOptionPane.ERROR_MESSAGE);
		}
		
		add(new Display());

		//pack();	
		setVisible(true);
	}
	
	private void close()
	{
		if (JOptionPane.showConfirmDialog(null, "Exit Program?",
				"Confirm Exit", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
		System.exit(0);
	}
	
	class Display extends JPanel
	{	
		
		public void paintComponent(Graphics g)
		{
			super.paintComponent(g);
			setBackground(Color.BLUE);
			g.drawImage(image, 50, 50, this);
			g.setColor(Color.WHITE);
			g.fillRect(0, 300, 500, 50);
			g.setColor(Color.RED);
			String caption = "Delicate Arch";
			Font	f = g.getFont();
			Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
			
			
			f = f.deriveFont(f.getSize2D() * 1.5F);				// enlarge font
			g.setFont(f);
			FontMetrics fm = g.getFontMetrics();
			g.drawString(caption, 180, 340);
		}
	}
	public static void main(String[] args)
	{
		new Arch();
	}

}