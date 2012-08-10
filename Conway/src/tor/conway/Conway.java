package tor.conway;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.Timer;

public class Conway extends JFrame implements KeyListener {
	private static final long serialVersionUID = -1685867618514404321L;
	protected static final char LIVE_CELL = 'O';
	protected static final int SIZE_FACTOR = 2;

	private enum State { RUNNING, STOPPED };

  private int generation;
  private State state;
  private Timer timer;
  protected World world;
 
  public Conway() {
    state = State.STOPPED;
    timer = new Timer(500, new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        Conway.this.timeStep(1);
      }
    });
    world = new World();
    /* Preliminary setup */
    this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		JFileChooser fc = new JFileChooser(".");
    /* Will set generation appropriately */
		do {
      if (fc.showOpenDialog(this) != JFileChooser.APPROVE_OPTION) {
        System.exit(1);
      }
    }
    while (!load(fc.getSelectedFile()));
    /* Prepare for display */
    this.addKeyListener(this);
    this.getContentPane().add(world);
    this.timeStep(0);
    this.pack();
	}
	
	protected void timeStep(int generations) {
		for (int i = 0; i < generations; ++i) { world.advance(); }
		this.setTitle("Conway's Game of Life (Generation: " + (generation += generations) + ")");
	}

	public void start() {
		if (!state.equals(State.RUNNING)) {
			state = State.RUNNING;
			timer.start();
		}
	}

	public void stop() {
		if (!state.equals(State.STOPPED)) {
			state = State.STOPPED;
			timer.stop();
		}
	}

	public boolean load(File f) {
		if (f == null) {
			System.err.println("[ERROR] Invalid file");
			return false;
		}
		String line;
		int longest_line = 0;
		BufferedReader reader;
		LinkedList<String> lines;
		try {
			lines = new LinkedList<String>();
			reader = new BufferedReader(new FileReader(f));
			try {
				while ((line = reader.readLine()) != null) {
					if (!line.trim().startsWith("!")) {
						lines.add(line);
						if (line.length() > longest_line) {
							longest_line = line.length();
						}
					}
				}
			} catch (IOException ioe) {
				ioe.printStackTrace();
			} finally {
				reader.close();
			}
		} catch (Exception e) {
			System.err.println("[ERROR] Cannot load: " + f.getName());
			return false;
		}
		System.out.println("[INFO] Loaded " + lines.size() + " line(s) from: " + f.getName());
		if (lines.isEmpty()) {
			System.err.println("[WARNING] Ignoring empty file");
			return false;
		}
		/* Otherwise, begin the resize procedure */
		world.reset(lines.size() * SIZE_FACTOR + 1, longest_line * SIZE_FACTOR + 1);
		int x = lines.size() * (SIZE_FACTOR - 1) / 2 + 1;
		int y = longest_line * (SIZE_FACTOR - 1) / 2 + 1;
		Iterator<String> it = lines.iterator();
		for (int i = 0; i < lines.size(); ++i) {
			line = it.next();
			for (int j = 0; j < line.length(); ++j) {
				if (line.charAt(j) == LIVE_CELL) {
					world.spawn(i + x, j + y);
				}
			}
		}
    /* Reset generation count */
		generation = 0;
		return true;
	}

	public boolean save(File f) {
		BufferedWriter writer;
		try {
			writer = new BufferedWriter(new FileWriter(f));
      /* TODO persist world */
			return true;
		} catch (Exception e) {
			System.err.println("[ERROR] Cannot save: " + f.getName());
			return false;
		}
	}

	@Override public void keyPressed(KeyEvent e) { }
	@Override public void keyReleased(KeyEvent e) {
		JFileChooser fc = new JFileChooser(".");
		switch (e.getKeyChar()) {
			case ' ' :
				if (state.equals(State.STOPPED)) {
					this.timeStep(1);
				}
			break;
			case 'l' :
				stop();
				fc.setSelectedFile(null);
				do {
					if (fc.getSelectedFile() != null) {
						JOptionPane.showMessageDialog(this, "Invalid file!", "Error", JOptionPane.ERROR_MESSAGE);
					}
					fc.showDialog(this, "Load World");
				} while (!load(fc.getSelectedFile()));
			break;
			case 'p' :
				switch (state) {
					case STOPPED : start(); break;
					default : case RUNNING : stop();
				}
			break;
			case 's' :
				fc.showDialog(this, "Save World");
				save(fc.getSelectedFile());
			break;
			case 'q' :
				this.dispose();
			break;
			default : e.consume();
		}
	}
	@Override public void keyTyped(KeyEvent e) { }

	public static void main(String... args) {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			@Override public void run() {
				new Conway().setVisible(true);
			}
		});
	}
}
