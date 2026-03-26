using GTA;
using GTA.Native;

namespace Boti {
    public class Main : Script {

        public bool menuVisible; 

        public Main() {
            Tick += OnTick;
            KeyDown += OnKeyDown;
        }

        public void OnTick(object s, EventArgs e) {

        }

        public void OnKeyDown(object a, KeyEventArgs e) {
            if(e.KeyCode == Keys.F7) {
                menuVisible = !menuVisible;
            }
        }
    }

    public class MenuPool {
        public List<Menu>  menus = new List<Menu>();

        public void Add(Menu m) {
            menus.Add(m);
        }

        public Menu activeMenu;

        public void Process() {
            if(activeMenu != null)
                activeMenu.Process
        }

        public void ProcessInput(KeyEventArgs e) {
            if(activeMenu != null) 
                activeMenu.ProcessInput(e);
        }
    }

    public class Menu {
        public bool isVisible;

        public int SelectedIndex = 0;

        public List<MenuItem> items = new List<MenuItem>();

        public void Process() {

        }

        public void ProcessInput(KeyEventArgs e) {
            if(e.KeyCode == Keys.Up)
                SelectedIndex--;

            if(e.KeyCode == Keys.Down)
                SelectedIndex++;

            if(e.KeyCode)

            if(SelectedIndex >= items.Length - 1) {
                SelectedIndex = 0;
            }
            else if(SelectedIndex < 0) {
                SelectedIndex = itens.Length - 1;
            }
        }
    }

    public class MenuItem {
        public string text;

        public EventHandler Activated;
    }
}