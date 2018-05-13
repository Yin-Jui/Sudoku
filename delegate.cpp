#include<QLineEdit>
#include<QIntValidator>
class Delegate : public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
                      const QModelIndex & index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        // Set validator
        QIntValidator *validator = new QIntValidator(0, 9, lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};
