#include <html_entity_lookup.h>

/*
 * call-seq:
 *  get(key)
 *
 * Get the HTML::EntityDescription for +key+
 */
static VALUE get(VALUE self, SEL sel, VALUE key)
{
  const htmlEntityDesc * desc =
    htmlEntityLookup((const xmlChar *)StringValuePtr(key));

  if(NULL == desc) return Qnil;
  VALUE klass = rb_const_get(mNokogiriHtml, rb_intern("EntityDescription"));

  VALUE args[3];
  args[0] = INT2NUM((long)desc->value);
  args[1] = NOKOGIRI_STR_NEW2(desc->name);
  args[2] = NOKOGIRI_STR_NEW2(desc->desc);

  return rb_class_new_instance(3, args, klass);
}

void init_html_entity_lookup()
{
  VALUE nokogiri = rb_define_module("Nokogiri");
  VALUE html = rb_define_module_under(nokogiri, "HTML");
  VALUE klass = rb_define_class_under(html, "EntityLookup", rb_cObject);

  rb_objc_define_method(klass, "get", get, 1);
}
