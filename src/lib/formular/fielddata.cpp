#include "fielddata.h"

const QStringList FieldData::types = QStringList() << QString::fromUtf8("Целое")
                                                        << QString::fromUtf8("Дробное")
                                                        << QString::fromUtf8("Масштабируемое")
                                                        << QString::fromUtf8("Перечисляемое")
                                                        << QString::fromUtf8("Константное")
                                                        << QString::fromUtf8("Логическое")
                                                        << QString::fromUtf8("Строковое")
                                                        << QString::fromUtf8("Неиспользуемое");

const QStringList FieldData::dimensions = QStringList()    << QString::fromUtf8("Метры")
                                                                << QString::fromUtf8("Километры")
                                                                << QString::fromUtf8("Мили")
                                                                << QString::fromUtf8("Метры в секунду")
                                                                << QString::fromUtf8("Узлы")
                                                                << QString::fromUtf8("Секунды")
                                                                << QString::fromUtf8("Микросекунды")
                                                                << QString::fromUtf8("Градусы")
                                                                << QString::fromUtf8("ТД")
                                                                << QString::fromUtf8("Радианы")
                                                                << QString::fromUtf8("Нет");
